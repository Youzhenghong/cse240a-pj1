#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "predictor.h"



void shift_pattern_reg(bool taken, int* pattern_reg);
void not_taken_shift(int* pattern_reg);
void taken_shift(int* pattern_reg);
void init_predictor();
int BHT_Index(int pc, int global_hist_reg, int shift);
char* deliminator = "-------------------------";

void not_taken_shift_test(int reg, int expected, int id) {
	shift_pattern_reg(false, &reg);
	assert(reg == expected);

	printf("%s#%d%s\n", "test", id, " passed");
}


void taken_shift_test(int reg, int expected, int id) {
	shift_pattern_reg(true, &reg);
	assert(reg == expected);

	printf("%s#%d%s\n", "test", id, " passed");
}


void BHT_Index_test(int pc, int reg, int expected, int shift, int id) {
	int addr = BHT_Index(pc, reg, shift);
	printf("%d\n", addr);
	assert(expected == addr);

	printf("%s#%d%s\n", "test", id, " passed");
}

void print_test_passed_msg(char * msg) {
	printf("%s %s %s\n", deliminator, msg, deliminator);
}


void run_tests() {
	init_predictor();


	printf("%s %s %s\n", deliminator, "start tests", deliminator);

	not_taken_shift_test(128, 128 >> 1, 0);
	not_taken_shift_test(130, 130 >> 1, 1);

	taken_shift_test(128, (128 >> 1) + (1 << (ghistoryBits - 1)), 2);
	taken_shift_test(68, (68 >> 1) + (1 << (ghistoryBits - 1)) ,3);

	BHT_Index_test(124124, 12244, 776, 10 ,4);



	printf("\n%s %s %s\n", deliminator, "end tests", deliminator);
}




