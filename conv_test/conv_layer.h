
#ifndef _CONV_LAYER_H
#define _CONV_LAYER_H

#define BATCH_SIZE 10
#define MAX_CONV_INPUT 8028160 
#define MAX_CONV_OUTPUT 8028160
#define S 2
#define K 7
#define ID 3
#define OD 64
#define IX 230
#define IY 230
#define OX 112
#define OY 112

using namespace std;

void conv_layer(float weights[K*K*ID*OD],
              float biases[MAX_CONV_OUTPUT],
              float input[MAX_CONV_INPUT*BATCH_SIZE],
              float output[MAX_CONV_OUTPUT*BATCH_SIZE],
              const int num_inputs,
              const int num_outputs,
              const int b,
	      const int od,
	      const int ox,
	      const int oy,
	      const int id,
	      const int ix,
	      const int iy,
	      const int s,
	      const int k);
#endif
