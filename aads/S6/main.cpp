#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "SortingTester.h"

int main(int argc, char* argv[])
{
  if (argc != 4) {
    std::cerr << "invalid arguments";
    return 1;
  }
  size_t count = std::strtoul(argv[3], nullptr, 10);
  if ((errno == ERANGE) || (count == 0)) {
    std::cerr << "invalid arguments";
    return 1;
  }
  std::string order = "";
  if (strcmp(argv[1], "ascending")) {
    order = "ascending";
  }
  else if (strcmp(argv[1], "descending")) {
    order = "descending";
  }
  else {
    std::cerr << "invalid arguments";
    return 1;
  }

  if (strcmp(argv[2], "ints") == 0) {
    std::vector< int > generatedNumbers;
    for (size_t i = 0; i < count; i++) {
      generatedNumbers.push_back(oleynikova::generateRandomNumber(1, 100));
    }
    if (order == "ascending") {
      oleynikova::SortingsTester< int, std::greater< int > > tester(generatedNumbers, std::cout, std::greater< int >());
      tester.test();
    }
    else if (order == "descending") {
      oleynikova::SortingsTester< int, std::less< int > > tester(generatedNumbers, std::cout, std::less< int >());
      tester.test();
    }
  }
  else if (strcmp(argv[2], "floats") == 0) {
    std::vector< float > generatedNumbers;
    for (size_t i = 0; i < count; i++) {
      generatedNumbers.push_back(oleynikova::generateRandomNumber(0.1f, 100.0f));
    }
    if (order == "ascending") {
      oleynikova::SortingsTester< float, std::greater< float > > tester(generatedNumbers, std::cout, std::greater< float >());
      tester.test();
    }
    else {
      oleynikova::SortingsTester< float, std::less< float > > tester(generatedNumbers, std::cout, std::less< float >());
      tester.test();
    }
  }
  else {
    std::cerr << "invalid arguments";
    return 1;
  }
  return 0;
}
