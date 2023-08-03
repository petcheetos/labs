#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include "Expression.h"

int main(int argc, char *argv[])
{
  oleynikova::Stack< long long > results;
  std::string string = "";
  if (argc == 2) {
    std::ifstream inputFile;
    inputFile.open(argv[1], std::ios::in);
    if (!inputFile.is_open()) {
      std::cerr << "File was not opened\n";
      return 1;
    }
    while (std::getline(inputFile, string)) {
      if (string == "") {
        continue;
      }
      try {
        results.push(oleynikova::getResult(string));
      }
      catch (std::runtime_error &e) {
        std::cerr << e.what();
        return 1;
      }
    }
    inputFile.close();
  }
  if (argc == 1) {
     while (std::cin.peek() != EOF) {
       std::getline(std::cin, string);
       if (string == "") {
         continue;
       }
       try {
         results.push(oleynikova::getResult(string));
       }
       catch (std::runtime_error &e) {
         std::cerr << e.what();
         return 1;
       }
     }
  }
  if (results.isEmpty()) {
    std::cout << '\n';
  }
  while (!results.isEmpty()) {
    std::cout << results.getTop();
    results.pop();
    if (results.getSize() != 0) {
      std::cout << ' ';
    }
    else {
      std::cout << '\n';
    }
  }
  return 0;
}
