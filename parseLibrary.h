#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "constants.h"

#pragma once


typedef enum {START_SECTOR, START_BLOCK, END_BLOCK, END_SECTOR, NO_MAGIC_KEY} magicKey_t;
typedef enum {PROCESSING_START_BLOCK, PROCESSING_MIDDLE_BLOCK, PROCESSING_FINAL_BLOCK} currentBlock_t;


typedef struct 
{
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
    uint8_t b4;
}state_t;



typedef struct 
{ 
    currentBlock_t   currentBlockState;  //which block of our statemachine are we currently at (start, middle, end?)
    uint32_t         uniqueId;           //the unique ID of a sector (will come in first block)
    int              blockIndex;         //used to keep track of which byte of a single block we are curently parsing
    state_t          shiftRegister;      //will keep track of last 4 bytes which are shifted in
    bool             processingSector;   //will be true once we start processing a secotr, will be set to false when we are done or we hit an error condition
    
    bool             validBlock0;
    bool             validBlock1;
    bool             validBlock2;
}validator_t;

magicKey_t searchForMagicBytes();
static void shiftIn(char in);
void processIncomingData(uint8_t in);
