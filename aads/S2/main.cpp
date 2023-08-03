#include <iostream>
#include <fstream>
#include <string>
#include <DictionaryOperations.h>
#include "Dictionary.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "invalid arguments";
    return 1;
  }
  std::ifstream inputFile;
  inputFile.open(argv[1], std::ios::in);
  if (!inputFile.is_open()) {
    std::cerr << "file did not open";
    return 1;
  }
  oleynikova::DictionaryOperations< oleynikova::Dictionary, std::string,
    oleynikova::Dictionary< int, std::string > > dictionaries(std::cout);
  dictionaries.inputDictionaries(inputFile);
  std::string command = "";
  while (std::getline(std::cin, command)) {
    if (command != "") {
      dictionaries.doCommands(command);
    }
  }
  inputFile.close();
  return 0;
}
