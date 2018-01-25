
#ifndef _CONV_LAYER_H
#define _CONV_LAYER_H

// Limits
#define MAX_BATCH 10
#define K 7
#define ID 3
#define OD 64
#define IX 230
#define IY 230
#define OX 112
#define OY 112
#define MAX_CONV_INPUT ID*IX*IY 
#define MAX_CONV_OUTPUT OD*OX*OY 

using namespace std;

void conv_layer(float weights[K*K*ID*OD],
              float biases[MAX_CONV_OUTPUT],
              float input[MAX_CONV_INPUT*MAX_BATCH],
              float output[MAX_CONV_OUTPUT*MAX_BATCH],
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
