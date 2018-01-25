#include <algorithm>
#include "fc_layer.h"

void fc_layer(float weights[MAX_INPUT_SIZE*MAX_OUTPUT_SIZE],
              float biases[MAX_OUTPUT_SIZE],
              float input[MAX_INPUT_SIZE*MAX_BATCH],
              float output[MAX_OUTPUT_SIZE*MAX_BATCH],
              const int batch_size,
              const int num_inputs,
              const int num_outputs)
{
  // Batch Iterator
  for (int b = 0; b < batch_size; b++) {

    // Output Node Iterator
    for (int o = 0; o < num_outputs; o++) {

      // Set bias
      output[b*num_outputs+o] = biases[o];

      // Accumulate weighted sum
      for (int i = 0; i < num_inputs; i++) {
        output[b*num_outputs+o] += input[b*num_inputs+i]*weights[o*num_inputs+i];
      }

      // Compute activation
      output[b*num_outputs+o] = std::max(0.0f, output[b*num_outputs+o]);
    }
  }
}
