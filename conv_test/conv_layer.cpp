
#include <algorithm>
#include "conv_layer.h"

void conv_layer(float weights[K*K*ID*OD],
              float biases[MAX_CONV_OUTPUT],
              float input[MAX_CONV_INPUT*BATCH_SIZE],
              float output[MAX_CONV_OUTPUT*BATCH_SIZE],
              const int num_inputs,
              const int num_outputs,
	      const int od,
	      const int ox,
	      const int oy,
	      const int id,
	      const int ix,
	      const int iy,
	      const int s,
	      const int k)
{
  //float * output = new float[OD*OY*OY];
  for (int b=0; b< BATCH_SIZE; b++){
      for (int o_d = 0; o_d < od; o_d++)
      {
        for (int o_y = 0; o_y < oy; o_y++)
        {
          for (int o_x = 0; o_x < ox; o_x++)
          {
            output[b*od*ox*oy +o_d*ox*oy + o_y*ox + o_x] = biases[o_d];

            // Do conv
            for (int i_d = 0; i_d < id; i_d++)
            {
              int iiy = 0;
              for (int i_y = o_y*s; i_y < o_y*s+k; i_y++)
              {
                int iix = 0;
                for (int i_x = o_x*s; i_x < o_x*s+k; i_x ++)
                {

                  output[b*od*ox*oy +o_d*ox*oy + o_y*ox + o_x] += 
                    (input[b*id*ix*iy+i_d*ix*iy+i_y*ix+i_x] *
                    weights[o_d*id*k*k + i_d*k*k + iiy*k + iix]);
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
}

