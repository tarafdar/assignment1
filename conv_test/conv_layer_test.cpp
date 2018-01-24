#include <iostream>
#include <fstream>
#include <cmath>
#include <cassert>
#include "conv_layer.h"
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


  std::string imageDir = "conv1";



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


  // (1, 3, 224, 224)

  // (1, 3, 230, 230)
  // (1, 64, 112, 112)
  // (64, 3, 7, 7)
  // (64)

  if (num_inputs < 0 || num_inputs > MAX_CONV_INPUT ||
      num_outputs < 0 || num_outputs > MAX_CONV_OUTPUT ||
      num_weights != ID*OD*K*K ||
      num_biases != OD)
  {
    cerr << "Problem with input files\n";
    retval = 1;
  }
  else{
	outputs = new float[BATCH_SIZE*num_outputs];
    // Run Accelerator
    conv_layer(weights, biases,
             inputs, outputs,
             num_inputs, num_outputs);


    // Check outputs
    float total = 0.0f;
    for (int i = 0; i < BATCH_SIZE*num_outputs; i++)
    {
      float err = fabs((outputs[i] - gold_outputs[i])/outputs[i]);
      if(outputs[i]!=0.0f)
	      total += err*err;
      if (err > 0.05)
      {
        cout << "Error " << i << ": "<< outputs[i] << " != " << gold_outputs[i] << " " << err << endl;
        retval = 1;
      }
    }
    float avg_error = total/(BATCH_SIZE *num_outputs);
    cout << "Average Square Error " << total << " " << (BATCH_SIZE * num_outputs) << " " << avg_error << endl;


  }
  //float * output = new float[OD*OY*OY];
  //for (int o_d = 0; o_d < 64; o_d++)
  //{
  //  for (int o_y = 0; o_y < OY; o_y++)
  //  {
  //    for (int o_x = 0; o_x < OX; o_x++)
  //    {
  //      output[o_d*OX*OY + o_y*OX + o_x] = biases[o_d];

  //      // Do conv
  //      for (int i_d = 0; i_d < ID; i_d++)
  //      {
  //        int iiy = 0;
  //        for (int i_y = o_y*S; i_y < o_y*S+K; i_y++)
  //        {
  //          int iix = 0;
  //          for (int i_x = o_x*S; i_x < o_x*S+K; i_x ++)
  //          {

  //            output[o_d*OX*OY + o_y*OX + o_x] += 
  //              inputs[i_d*IX*IY+i_y*IX+i_x] *
  //              weights[o_d*ID*K*K + i_d*K*K + iiy*K + iix];
  //              //weights[o_d*ID*K*K + i_d*K*K + (i_y-o_y)*K + (i_x-o_x)];
  //              iix++;
  //          }
  //          iiy++;
  //        }
  //      }

  //      output[o_d*OX*OY + o_y*OX + o_x] = max(float(0.), output[o_d*OX*OY + o_y*OX + o_x]);
  //    }
  //  }
  //}
  //for (int o_d = 0; o_d < 1; o_d++)
  //{
  //  for (int o_y = 0; o_y < 10; o_y++)
  //  {
  //    for (int o_x = 0; o_x < 10; o_x++)
  //    {
  //      cout << output[o_d*OX*OY + o_y*OX + o_x] << " != " 
  //           << gold_outputs[o_d*OX*OY + o_y*OX + o_x] << endl;
  //    }
  //  }
  //}

  return 0;
}

