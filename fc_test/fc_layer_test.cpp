#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "fc_layer.h"
#include "/workspace/assignment1/util/shared.h"
using namespace std;


int main()
{
  float * weights;
  float * biases;
  float * inputs;
  float * gold_outputs;
  float * outputs;
  int retval = 0;
  
  std::string imageDir = "fc1";
  int num_inputs = readFile(("/workspace/assignment1/nn_params/" + imageDir + "/input").c_str(), inputs)/BATCH_SIZE;
  int num_outputs = readFile(("/workspace/assignment1/nn_params/" +imageDir + "/output").c_str(), gold_outputs)/BATCH_SIZE;
  int num_weights = readFile(("/workspace/assignment1/nn_params/" + imageDir + "/weights").c_str(), weights);
  int num_biases = readFile(("/workspace/assignment1/nn_params/" + imageDir +"/biases").c_str(), biases);

  cout << "Begin Test\n"
       << "Batch Size: " << BATCH_SIZE << "\n"
       << "Num Inputs: " << num_inputs << "\n"
       << "Num Outputs: " << num_outputs << "\n"
       << "Num Weights: " << num_weights << "\n"
       << "Num Biases: " << num_biases << endl;
  cout << "input ptr: " << weights << endl;

  if (num_inputs < 0 || num_inputs > MAX_INPUT ||
      num_outputs < 0 || num_outputs > MAX_OUTPUT ||
      num_weights != num_inputs*num_outputs ||
      num_biases != num_outputs)
  {
    cerr << "Problem with input files\n";
    retval = 1;
  }
  else
  {
	  // Allocate space for accelerator outputs
	  outputs = new float[BATCH_SIZE*num_outputs];
    // Run Accelerator
    fc_layer(weights, biases,
             inputs, outputs,
             num_inputs, num_outputs);

    // Check outputs
    float total = 0.0f;
    for (int i = 0; i < BATCH_SIZE*num_outputs; i++)
    {
      float err = fabs((outputs[i] - gold_outputs[i]));
      total += err*err;
    }
    float avg_error = total/(BATCH_SIZE *num_outputs);
    cout << "Average Square Error " << total << " " << (BATCH_SIZE * num_outputs) << " " << avg_error << endl;
  }
  return retval;
}
