#include "DictionaryOperations.h"
#include <string>
#include <vector>

std::vector< std::string > oleynikova::split(std::string str)
{
  std::vector< std::string > result;
  size_t start = 0;
  size_t end = 0;
  while ((end = str.find(' ', start)) != std::string::npos) {
    result.push_back(str.substr(start, end - start));
    start = end + 1;
  }
  result.push_back(str.substr(start));
  return result;
}
