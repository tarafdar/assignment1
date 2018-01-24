#ifndef _FC_LAYER_H
#define _FC_LAYER_H

#define BATCH_SIZE 10
#define MAX_INPUT 1024
#define MAX_OUTPUT 1024

void fc_layer(float weights[MAX_INPUT*MAX_OUTPUT],
              float biases[MAX_OUTPUT],
              float input[MAX_INPUT*BATCH_SIZE],
              float output[MAX_OUTPUT*BATCH_SIZE],
              const int num_inputs,
              const int num_outputs);

#endif
