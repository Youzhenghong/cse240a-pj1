//========================================================//
//  predictor.c                                           //
//  Source file for the Branch Predictor                  //
//                                                        //
//  Implement the various branch predictors below as      //
//  described in the README                               //
//========================================================//
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "predictor.h"

//
// TODO:Student Information
//
const char *studentName = "Zhenghong You";
const char *studentID   = "A53252773";
const char *email       = "yzhengho@eng.ucsd.edu";
// global functions
int read_branch(uint32_t *pc, uint8_t *outcome);



//------------------------------------//
//      Predictor Configuration       //
//------------------------------------//

// Handy Global for use in output routines
const char *bpName[4] = { "Static", "Gshare",
                          "Tournament", "Custom" };

int ghistoryBits; // Number of bits used for Global History
int lhistoryBits; // Number of bits used for Local History
int pcIndexBits;  // Number of bits used for PC index
int bpType;       // Branch Prediction Type
int verbose;

//------------------------------------//
//      Predictor Data Structures     //
//------------------------------------//

//
//TODO: Add your own Branch Predictor data structures here
//
int global_hist_reg;
int local_hist_reg;
int GLOBAL_T_MASK;
uint8_t bht[BHT_SIZE];
//------------------------------------//
//        Predictor Functions         //
//------------------------------------//

/*
 T         N
0000  -> 1000 -> 0100
1000  -> 0000


*/


// Initialize the predictor
//
void
init_predictor()
{
  //
  //TODO: Initialize Branch Predictor Data Structures
  //
    GLOBAL_T_MASK = 1 << (ghistoryBits - 1);
    global_hist_reg = 0;
    local_hist_reg = 0;
    
    for (int i = 0; i < BHT_SIZE; i++) {
        bht[i] = SN;
    }

}


int BHT_Index(int pc, int global_hist_reg, int shift) {

     int mask = (int)pow(2, shift) - 1;
     return (pc ^ global_hist_reg) & mask;
}

void shift_pattern_reg(bool taken, int* pattern_reg) {
    if (taken) {
      taken_shift(pattern_reg);
    } else {
      not_taken_shift(pattern_reg);
    }
}

void not_taken_shift(int* pattern_reg) {
    *pattern_reg = (*pattern_reg >> 1);
}

void taken_shift(int* pattern_reg) {
    *pattern_reg = (*pattern_reg >> 1) | GLOBAL_T_MASK;
}

uint8_t bhtLookUpHelper(uint8_t flag) {
    if (flag < 2) {
        return NOTTAKEN;
    } else {
        return TAKEN;
    }
}

void updateBHT(int index, bool flag) {
    if (flag) {
        bht[index] = MIN(3, bht[index] + 1);
    } else {
        bht[index] = MAX(0, bht[index] - 1);
    }
}
//gshare prediction
uint8_t 
gSharePredict(uint32_t pc) {
    int BHTAddress = BHT_Index(pc, global_hist_reg, ghistoryBits);
    uint8_t pred = bhtLookUpHelper(bht[BHTAddress]);
    uint8_t outcome = NOTTAKEN;
    read_branch(&pc, &outcome);

    if (outcome == pred) {
        updateBHT(BHTAddress, true);
    } else {
        updateBHT(BHTAddress, false);
    }
    return pred;
}



// Make a prediction for conditional branch instruction at PC 'pc'
// Returning TAKEN indicates a prediction of taken; returning NOTTAKEN
// indicates a prediction of not taken
//
uint8_t
make_prediction(uint32_t pc)
{
  //
  //TODO: Implement prediction scheme
  //

  // Make a prediction based on the bpType
  switch (bpType) {
    case STATIC:
      return TAKEN;
    case GSHARE:
      return gSharePredict(pc);
    case TOURNAMENT:
    case CUSTOM:
    default:
      break;
  }

  // If there is not a compatable bpType then return NOTTAKEN
  return NOTTAKEN;
}

// Train the predictor the last executed branch at PC 'pc' and with
// outcome 'outcome' (true indicates that the branch was taken, false
// indicates that the branch was not taken)
//
void
train_predictor(uint32_t pc, uint8_t outcome)
{
  //
  //TODO: Implement Predictor training
  //
}
