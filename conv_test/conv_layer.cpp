#include <algorithm>
#include "conv_layer.h"

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
	      const int k)
{
  // Batch
  for (int b_=0; b_< b; b_++)
  {
    // Output Dimensions (Feature Maps)
    for (int o_d = 0; o_d < od; o_d++)
    {
      // Output Y Dimension
      for (int o_y = 0; o_y < oy; o_y++)
      {
        // Output X Dimension
        for (int o_x = 0; o_x < ox; o_x++)
        {
          // Set bias 
          output[b_*od*ox*oy +o_d*ox*oy + o_y*ox + o_x] = biases[o_d];

          // Weighted Sum:
   
          // Input Dimensions (Feature Maps)
          for (int i_d = 0; i_d < id; i_d++)
          {
            // Input Y Dimension
            for (int i_y = o_y*s, iiy = 0; i_y < o_y*s+k; i_y++, iiy++)
            {
              // Input X Dimension
              for (int i_x = o_x*s, iix = 0; i_x < o_x*s+k; i_x++, iix++)
              {
                output[b_*od*ox*oy + o_d*ox*oy + o_y*ox + o_x] += 
                       (input[b_*id*ix*iy + i_d*ix*iy + i_y*ix + i_x] *
                       weights[o_d*id*k*k + i_d*k*k + iiy*k + iix]);
              }
            }
          }

          // Activaton Function
          output[b_*od*ox*oy + o_d*ox*oy + o_y*ox + o_x] = 
                 max(0.0f, output[b_*od*ox*oy + o_d*ox*oy + o_y*ox + o_x]);
        }
      }
    }
  }
}

