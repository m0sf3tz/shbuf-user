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
#include "parseLibrary.h"
#include "constants.h"

#define DATA_LENGHT SHBUF0_SIZE

uint32_t totalTransfered = 0; //includes all of the bytes which are transfered to date. 

int main(int argc, char *argv[])
{
    char * shbuf_loc = "/dev/shbuf";
    char * pru_loc   = "/dev/pru_ctrl";
   
    //copy from kernal space a buffer into this guy
    char tempBuf[TOTAL_BYTES_IN_SECTOR];
    
    u_int32_t t;
    u_int32_t counter;
    u_int32_t retVal;
    
    FILE * fds;
    FILE * fdp;
    FILE *ptr_myfile;
    
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
    

/*
	ptr_myfile=fopen("log.bin","wb");
	if (!ptr_myfile)
	{
		printf("Unable to open file!");
		return 1;
	}
  */  

    int q;

    //reset the spinlocks subsystem
    ioctl(fds, SPINLOCK_RESET, &q);
    
    printf("enabling PRU\n"); 

    ioctl(fdp, PRU_START_EXECUTING, &q);

    printf("PRU execution started\n"); 
     

    printf("reading some bytes..\n"); 

    do{
        
        sleep(1);
        
        retVal = read(fds, tempBuf, TOTAL_BYTES_IN_SECTOR);  
                
        if(retVal)
        {            
            for(counter = 0; counter < TOTAL_BYTES_IN_SECTOR; counter++)
            {
                totalTransfered++;
                processIncomingData(tempBuf[counter]);
            }
                       
        }           
        
    }while(1);  


    close(fds);
    close(fdp);
    //close(ptr_myfile);
       
    return 0;
}
