#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  while (!std::cin.eof()) {
    std::cin.clear();
    std::vector< oleynikova::DataStruct > data;
    std::copy(
      std::istream_iterator< oleynikova::DataStruct >(std::cin),
      std::istream_iterator< oleynikova::DataStruct >(),
      std::back_inserter(data)
    );
    std::sort(data.begin(), data.end());
    std::copy(
      std::begin(data),
      std::end(data),
      std::ostream_iterator<oleynikova::DataStruct >(std::cout, "\n")
    );
  }
  return 0;
}
