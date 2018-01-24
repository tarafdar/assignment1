#include <algorithm>
#include "fc_layer.h"

void fc_layer(float weights[MAX_INPUT*MAX_OUTPUT],
              float biases[MAX_OUTPUT],
              float input[MAX_INPUT*BATCH_SIZE],
              float output[MAX_OUTPUT*BATCH_SIZE],
              const int num_inputs,
              const int num_outputs)
{
  // Batch Iterator
  fc_layer_label0:for (int b = 0; b < BATCH_SIZE; b++) {
    // Output Node Iterator
    fc_layer_label1:for (int o = 0; o < num_outputs; o++) {
      // Set bias
      output[b*num_outputs+o] = biases[o];

      // Accumulate weighted sum
      fc_layer_label2:for (int i = 0; i < num_inputs; i++) {

        output[b*num_outputs+o] += input[b*num_inputs+i]*weights[o*num_inputs+i];
      }

      // Compute activation
      output[b*num_outputs+o] = std::max(float(0.), output[b*num_outputs+o]);
    }
  }
}
