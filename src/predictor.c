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
