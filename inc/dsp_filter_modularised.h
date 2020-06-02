#ifndef DSP_FILTER_MODULARISED_H
#define DSP_FILTER_MODULARISED_H

#define TEST_LENGTH_SAMPLES 320 // defines the length of the input, might need to bump it up later
#define NUM_TAPS 31
#define BLOCK_SIZE 32 // how many samples to process at 1 go, might change later

#include "arm_math.h"
#include "math_helper.h"

float32_t* low_pass_filtered (float32_t* input, bool print_snr);
#endif