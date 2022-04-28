// not using full samples due to data transformation complexity
// eg. having to split a pasted string from google spreadsheet by newline
// and then turn it into the matching map below

#include <map>

std::map<int, float> u2DepthValsMap = {
  {12345, 12},
  {12346, 12},
  {12347, 12}
};

std::map<int, float> u1DepthValsMap = {
  {12345, 12},
  {12346, 12},
  {12347, 12}
};

std::map<int, float> m1DepthValsMap = {
  {12345, 17},
  {12346, 17},
  {12347, 17}
};

std::map<int, float> d1DepthValsMap = {
  {12345, 20},
  {12346, 20},
  {12347, 20}
};

std::map<int, float> d2DepthValsMap = {
  {12345, 12},
  {12346, 12},
  {12347, 12}
};