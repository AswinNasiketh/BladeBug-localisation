#include "arm_math.h"
#include "math_helper.h"

#define TEST_LENGTH_SAMPLES 320 // defines the length of the input, might need to bump it up later
#define NUM_TAPS 32 //because the arm_fir_init_q15 function requires even number of taps
#define BLOCK_SIZE 32 // how many samples to process at 1 go, might change later

const float32_t firCoeffs32[NUM_TAPS] = { // the coefficient generated from matlab code
    0.00987575366521376, -0.0479952189591824, -0.00600838976898258, 0.0107666799171830,
    0.0223029458508225,	0.0252533422491029,	0.0145487810254858,	-0.00866009155285300,
    -0.0347976296133383, -0.0486578890548093, -0.0359695331986386, 0.00922182054442052,	
    0.0800240036174069,	0.157629993494741,	0.217830476339031,	0.240495542556797,	
    0.217830476339031,	0.157629993494741,	0.0800240036174069,	0.00922182054442052,
    -0.0359695331986386, -0.0486578890548093, -0.0347976296133383, -0.00866009155285300,
    0.0145487810254858,	0.0252533422491029,	0.0223029458508225,	0.0107666799171830,	
    -0.00600838976898258, -0.0479952189591824, 0.00987575366521376, 0
}
q15_t* firCoeffsQ15;
void arm_float_to_q15 (firCoeffs32, firCoeffsQ15, NUM_TAPS); // converts the float values to Q15 values

uint32_t blockSize = BLOCK_SIZE;
uint32_t numBlocks = TEST_LENGTH_SAMPLES / BLOCK_SIZE;


q15_t* low_pass_filtered (q15_t* input){

    static q15_t testOutput[TEST_LENGTH_SAMPLES]; //setup the test output buffer
    static q15_t firStateQ15[BLOCK_SIZE + NUM_TAPS - 1];

    arm_fir_instance_q15 S;
    are_status status;
  
    /* Initialize input and output buffer pointers */
    q15_t *inputQ15, *outputQ15;
    inputQ15 = &input[0];
    outputQ15 = &testOutput[0];

    /* Call FIR init function to initialize the instance structure. */
    arm_fir_init_q15 (&S, NUM_TAPS, (q15_t *)&firCoeffsQ15[0], &firStateQ15[0], blockSize);

    // Call the FIR process function for every blockSize sample
    for(uint32_t i=0; i < numBlocks; i++){
    arm_fir_f32(&S, inputQ15 + (i * blockSize), outputQ15 + (i * blockSize), blockSize);
    }


    return outputQ15;
}