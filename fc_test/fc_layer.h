#ifndef _FC_LAYER_H
#define _FC_LAYER_H

#define MAX_BATCH 10
#define MAX_INPUT_SIZE 1024
#define MAX_OUTPUT_SIZE 1024

void fc_layer(float weights[MAX_INPUT_SIZE*MAX_OUTPUT_SIZE],
              float biases[MAX_OUTPUT_SIZE],
              float input[MAX_INPUT_SIZE*MAX_BATCH],
              float output[MAX_OUTPUT_SIZE*MAX_BATCH],
              const int batch_size,
              const int num_inputs,
              const int num_outputs);

#endif
