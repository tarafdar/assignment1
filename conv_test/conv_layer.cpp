
#include <algorithm>
#include "conv_layer.h"

void conv_layer(float weights[K*K*ID*OD],
              float biases[MAX_CONV_OUTPUT],
              float input[MAX_CONV_INPUT*BATCH_SIZE],
              float output[MAX_CONV_OUTPUT*BATCH_SIZE],
              const int num_inputs,
              const int num_outputs)
{
  //float * output = new float[OD*OY*OY];
  for (int o_d = 0; o_d < OD; o_d++)
  {
    for (int o_y = 0; o_y < OY; o_y++)
    {
      for (int o_x = 0; o_x < OX; o_x++)
      {
        output[o_d*OX*OY + o_y*OX + o_x] = biases[o_d];

        // Do conv
        for (int i_d = 0; i_d < ID; i_d++)
        {
          int iiy = 0;
          for (int i_y = o_y*S; i_y < o_y*S+K; i_y++)
          {
            int iix = 0;
            for (int i_x = o_x*S; i_x < o_x*S+K; i_x ++)
            {

              output[o_d*OX*OY + o_y*OX + o_x] += 
                input[i_d*IX*IY+i_y*IX+i_x] *
                weights[o_d*ID*K*K + i_d*K*K + iiy*K + iix];
                //weights[o_d*ID*K*K + i_d*K*K + (i_y-o_y)*K + (i_x-o_x)];
                iix++;
            }
            iiy++;
          }
        }

        output[o_d*OX*OY + o_y*OX + o_x] = max(float(0.), output[o_d*OX*OY + o_y*OX + o_x]);
      }
    }
  }

}

