#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "constants.h"
#include "parseLibrary.h"

//we will overshoot because we won't know we got a end magic number until we actually read it, hence + STOP_SEQUENCE_SIZE

uint8_t tempBlock0[TRASMIT_BLOCK_SIZE+STOP_SEQUENCE_SIZE]; 
uint8_t tempBlock1[TRASMIT_BLOCK_SIZE+STOP_SEQUENCE_SIZE];
uint8_t tempBlock2[TRASMIT_BLOCK_SIZE+STOP_SEQUENCE_SIZE];

validator_t validator;

extern uint32_t totalTransfered; //includes all of the bytes which are transfered to date. 

magicKey_t searchForMagicBytes()
{
    uint32_t magicByte32 =   validator.shiftRegister.b0 << 0u  |
                             validator.shiftRegister.b1 << 8u  |
                             validator.shiftRegister.b2 << 16u |
                             validator.shiftRegister.b3 << 24u;

    
 
    uint64_t magicByte64  =  magicByte32 | (uint64_t)validator.shiftRegister.b4<< 32ull;
    #if 0
    printf("first byte is : %x ! \n", validator.shiftRegister.b0);
    printf("second byte is: %x ! \n", validator.shiftRegister.b1);
    printf("third byte is : %x ! \n", validator.shiftRegister.b2);
    printf("fourth byte is: %x ! \n", validator.shiftRegister.b3);
    printf("fifth byte is : %x ! \n", validator.shiftRegister.b4);

    printf("\n");
    printf("\n");
    #endif 
        
   
        
    if(magicByte32 == NEW_TRANSMIT_HEADER_32_BITS)
    {
        printf("Got an start sector magic number! with byte %d \n", totalTransfered);
        return START_SECTOR;
    }
    else if(magicByte32 == TRANSMIT_HEADER_32_BITS)
    {
        printf("Got an start block magic number! with byte %d \n", totalTransfered);
        return START_BLOCK;
    }
    
    //end magic numbers are 5bytes (why?)
    if(magicByte64 == STOP_SEQUENCE_64_BITS)
    {
        printf("Got an end block magic number! with byte %d \n", totalTransfered);
        return END_BLOCK;
    }
    else if(magicByte64 == FINAL_STOP_SEQUENCE_64_BITS)
    {
        printf("Got an end sector magic number! with byte %d \n", totalTransfered);
        return END_SECTOR;
    }

    return NO_MAGIC_KEY;
    
}

//used to keep track of the last 5 byes we got
static void shiftIn(char in)
{
   validator.shiftRegister.b4 = validator.shiftRegister.b3;
   validator.shiftRegister.b3 = validator.shiftRegister.b2;
   validator.shiftRegister.b2 = validator.shiftRegister.b1;
   validator.shiftRegister.b1 = validator.shiftRegister.b0;
   validator.shiftRegister.b0 = in;
}

void processIncomingData(uint8_t in)
{
    shiftIn(in);
    magicKey_t key = searchForMagicBytes();
 
    /*
    switch(validator.currentBlockState){
    
        case PROCESSING_START_BLOCK:
            //if we get the magic number saying we will be transmitting a new sector, reset our states
            if(START_SECTOR  == key)
            {
                validator.processingSector = true;
                validator.blockIndex = 0;
                break;
            }
            else if(END_BLOCK  == key)  
            {
                //got the first sector, go to next state 

                validator.currentBlockState = PROCESSING_MIDDLE_BLOCK;
                validator.blockIndex = 0;               

                printf("Processed the first block of a sector \n");

                break;
            }
            else if(START_BLOCK  == key)  
            {
                //error, we should not be getting here - expect only END_BLOCK
                validator.processingSector = false;
                validator.blockIndex = 0;
                break;
            }
            else if(END_SECTOR  == key)  
            {
                //error, we should not be getting here - expect only END_BLOCK
                validator.processingSector = false;
                validator.blockIndex = 0;
                break;
            }
            else
            {
                //we did not hit a magic key
                //only read in starting from immidialty after the initial magic number, and up to 1 CRC protected section)
                if(validator.blockIndex  ==  TRASMIT_BLOCK_SIZE_START_END_MAGIC)
                {
                      validator.processingSector = false;
                }
                
                if(validator.processingSector)
                {
                    tempBlock0[validator.blockIndex] = in;
                }
                
                validator.blockIndex++;
            }
            if(validator.blockIndex > TRASMIT_BLOCK_SIZE - NEW_TRASMITION_HEADER_SIZE - FINAL_STOP_SEQUENCE_SIZE)
            {
                //error, we should not be getting here - expect only END_BLOCK
                validator.processingSector = false;
                validator.blockIndex = 0;
                break;
            }
       }
       */
}

