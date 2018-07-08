#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>


#include "shbuf_ioctl.h"
#include "pru_ioctl.h"
#include "sharedVariables.h"
#include "lfsr.h"

#define DATA_LENGHT SHBUF0_SIZE

void makePerfect(char * temp, int len, lfsr_t * rand)
{
    while(len--){
        *(uint32_t*)temp = (rand->data & 0xFF);
        GLFSR_next(rand);
        temp = temp+1;
    }
}



int main(int argc, char *argv[])
{
    char * shbuf_loc = "/dev/shbuf";
    char * pru_loc   = "/dev/pru_ctrl";
   
    lfsr_t glfsr_d0;
    uint32_t sigmaRead = 0;
    uint64_t poly = 0x1081;
    GLFSR_init(&glfsr_d0, poly, 0xdeadbeef);
   
    char transfered[SHBUF0_SIZE];
    char calculated[SHBUF0_SIZE];
    
    u_int32_t t;
    uint32_t readSize;
    uint32_t readTotal; //how much we actually read when we requested... might not always be the saem ;)
    
    
    FILE * fds;
    FILE * fdp;

    fds = open(shbuf_loc, O_RDWR);
    if (fds == -1)
    {
        perror("could not open shbuf driver");
        return 2;
    }
    
    fdp = open(pru_loc, O_RDWR);
    if (fdp == -1)
    {
        perror("could not open pru driver");
        return 2;
    }

    int q;

    //reset the spinlocks subsystem
    ioctl(fds, SPINLOCK_RESET, &q);
    
    printf("enabling PRU\n"); 

    ioctl(fdp, PRU_START_EXECUTING, &q);

    printf("PRU execution started\n"); 
     

    printf("reading some bytes..\n"); 


    do{
        readSize = glfsr_d0.data%SHBUF0_SIZE;
        
        printf("Trying to read %d bytes!! \n", readSize);
        
        readTotal = read(fds, transfered, readSize);  
        
        sigmaRead = sigmaRead + readTotal;
        
        printf("Read %d Bytes!! \n", readTotal);
        
        printf("Read total of  %d Bytes!! \n", sigmaRead);
    
        makePerfect(calculated, readTotal, &glfsr_d0);
        

        q = memcmp(calculated, transfered, readTotal);

        
        if(q){
            printf("Failed to get a match! \n");
            break;
        }
        
        printf("Read checked out!! \n");
        printf("\n");
       
                    
    }while(1);
    

    close(fds);
    close(fdp);
    
    return 0;
}
