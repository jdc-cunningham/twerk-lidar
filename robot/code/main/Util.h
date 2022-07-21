#include <math.h>

// https://stackoverflow.com/a/29447688/2710227
float rounUp(float val)
{
  return roundf(val * 100) / 100;
}

// this does not belong here
void saveDataLocally()
{
  // std::map<std::string, std::map<float, float>> scanSampleValues = {};

  // for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  // {
  //   Serial.println(it->first);
  // }

  // for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  // {
  //   Serial.println(it->second);
  // }
}