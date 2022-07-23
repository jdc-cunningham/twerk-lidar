#include <math.h>

// https://stackoverflow.com/a/29447688/2710227
float roundUp(float val)
{
  return roundf(val * 100) / 100;
}
