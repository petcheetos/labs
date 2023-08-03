#include <iostream>
#include <fstream>
#include <cstring>
#include "Commands.h"

int main(int argc, char* argv[])
{
  int exit = 0;
  std::cout << "Type -help to show information\n";
  if (argc == 1) {
    oleynikova::Commands commands(std::cin, std::cout);
    while (exit == 0) {
      commands.inputCommand(exit);
    }
  }
  else if (argc == 3) {
    std::fstream file(argv[2]);
    if (!file.is_open()) {
      std::cerr << "File was not opened";
      return 1;
    }
    if (strcmp(argv[1], "input") == 0) {
      oleynikova::Commands commands(file, std::cout);
      commands.inputData();
      while (exit == 0) {
        commands.inputCommand(exit);
      }
    }
    else if (strcmp(argv[1], "output") == 0) {
      oleynikova::Commands commands(std::cin, file);
      while (exit == 0) {
        commands.inputCommand(exit);
        if (exit == 2) {
          std::fstream(argv[2], std::fstream::out);
          exit = 0;
        }
      }
    }
    file.close();
  }
  else if (argc == 4) {
    std::ifstream inputFile(argv[2]);
    std::ofstream outputFile(argv[3]);
    if (!inputFile.is_open() || !outputFile.is_open()) {
      std::cerr << "File was not opened";
      return 1;
    }
    oleynikova::Commands commands(inputFile, outputFile);
    commands.inputData();
    while (exit == 0) {
      commands.inputCommand(exit);
    }
    inputFile.close();
    outputFile.close();
  }
  else {
    std::cerr << "invalid arguments\n";
    return 1;
  }
  return 0;
}
