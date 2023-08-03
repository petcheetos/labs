#include "FunctorStruct.h"
#include <limits>
#include <stdexcept>

oleynikova::NodeSumm::NodeSumm():
  keyResult(0),
  stringResult("")
{}

void oleynikova::NodeSumm::operator()(const std::pair< int, std::string >& node)
{
  static const int MAX_INT = std::numeric_limits< int >::max();
  static const int MIN_INT = std::numeric_limits< int >::min();
  if (node.first < 0) {
    if ((MIN_INT - node.first) > keyResult) {
      throw std::runtime_error("Underflow");
    }
  }
  if (node.first > 0) {
    if ((MAX_INT - node.first) < keyResult) {
      throw std::runtime_error("Overflow");
    }
  }
  keyResult += node.first;
  if (stringResult == "") {
    stringResult += node.second;
  }
  else {
    stringResult = stringResult + ' ' + node.second;
  }
}
