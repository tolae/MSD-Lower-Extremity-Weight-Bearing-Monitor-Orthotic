#include <Arduino.h>
#include "inc/convolution.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

void convolve(int *filter, int *in_data, unsigned int f_len, unsigned int in_len, int *out_data, unsigned int *out_len)
{
  unsigned int cnv_len = in_len + f_len - 1;
  (*out_len) = cnv_len;

  for (unsigned int i; i < cnv_len; i++)
  {
    unsigned int f_start = MIN(i, f_len - 1);
    unsigned int in_start = MAX(0, i - f_len + 1);
    unsigned int in_end = MIN(i + 1, in_len);

    for (unsigned int j = in_start; j < in_end; j++)
    {
      out_data[i] = filter[f_start--] * in_data[j];
    }
  }
}
