#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include <vector>
#include <stdlib.h>
#include "conv_layer.h"
#include "util/shared.h"

using namespace std;

int main()
{
  float * weights;
  float * biases;
  float * inputs;
  float * gold_outputs;
  float * outputs;
  int retval = 0;

  cout << "Starting Convolution Test " << endl;

  std::string imageDir = "nn_params/conv1_7x7_s2/";
  std::vector<int> input_params = readFile(imageDir + "/input", inputs, MAX_CONV_INPUT *MAX_BATCH);
  std::vector<int> output_params = readFile(imageDir + "/output", gold_outputs, MAX_CONV_OUTPUT * MAX_BATCH);
  std::vector<int> weight_params = readFile(imageDir + "/weights", weights, ID*OD*K*K);
  std::vector<int> bias_params = readFile(imageDir +"/biases", biases, OD);

  int num_inputs = 1;
  int num_outputs = 1;
  int num_weights = 1;
  int num_biases = 1;

  for(int i=1; i<input_params.size();i++){
      num_inputs*=input_params[i];
  }
  for(int i=1; i<output_params.size();i++){
      num_outputs*=output_params[i];
  }

  for(int i=0; i<weight_params.size();i++){
        num_weights*=weight_params[i];
  }
  
  for(int i=0; i<bias_params.size();i++)
      num_biases*=bias_params[i];

  if (num_inputs < 0 || num_inputs > MAX_CONV_INPUT ||
      num_outputs < 0 || num_outputs > MAX_CONV_OUTPUT ||
      num_weights > ID*OD*K*K ||
      num_biases > OD)
  {
    cerr << "Problem with input files\n";
    retval = 1;
  }
  else {
    outputs = new float[MAX_BATCH*MAX_CONV_OUTPUT];
   
    int b = input_params[0];  
    int od = output_params[1];  
    int ox = output_params[2];  
    int oy = output_params[3];  
    int id = input_params[1];  
    int ix = input_params[2];  
    int iy = input_params[3];  
    int k = weight_params[3];
    int s = (ix-k)/(ox-1);

    cout << "kernel size " << k << endl;
    cout << "id " << id << endl;
    cout << "od " << od << endl;
    cout << "ox " << ox << endl;
    cout << "oy " << oy << endl;
    cout << "s " << s << endl;
    cout << "id " << id << endl;
    cout << "ix " << ix << endl;
    cout << "iy " << iy << endl;

    cout << "Begin Test\n"
       << "Batch Size: " << b << "\n"
       << "Num Inputs: " << num_inputs << "\n"
       << "Num Outputs: " << num_outputs << "\n"
       << "Num Weights: " << num_weights << "\n"
       << "Num Biases: " << num_biases << endl 
       << "Num Stride: " << s << endl;

 
    // Run Accelerator
    conv_layer(weights, biases,
               inputs, outputs,
               b, od, ox, oy, id, ix, iy, s, k);


    // Check outputs
    float total = 0.0f;
    for (int i = 0; i < b*num_outputs; i++)
    {
      float err = fabs(outputs[i] - gold_outputs[i]);
      total += err*err;
    }
    float avg_error = total/(b *num_outputs);
    cout << "Mean Square Error " << avg_error << endl;
  }

  return retval;
}

