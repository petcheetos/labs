#include <iostream>
#include <fstream>
#include "Commands.h"

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Invalid arguments";
    return 1;
  }
  std::ifstream inputFile;
  inputFile.open(argv[1], std::ios::in);
  if (!inputFile.is_open()) {
    std::cerr << "File did not open";
    return 1;
  }
  oleynikova::Commands commands(std::cout, std::cin);
  const std::map< std::string, std::function< void() > > functions({
    {"AREA", std::bind(&oleynikova::Commands::doArea, std::ref(commands))},
    {"MAX", std::bind(&oleynikova::Commands::doMax, std::ref(commands))},
    {"MIN", std::bind(&oleynikova::Commands::doMin, std::ref(commands))},
    {"MAXSEQ", std::bind(&oleynikova::Commands::doMaxSeq, std::ref(commands))},
    {"RIGHTSHAPES", std::bind(&oleynikova::Commands::doRightShapes, std::ref(commands))},
    {"COUNT", std::bind(&oleynikova::Commands::doCount, std::ref(commands))}
  });
  commands.inputData(inputFile);
  while (!std::cin.eof()) {
    std::istream::sentry sentry(std::cin);
    if (!sentry) {
      break;
    }
    std::string command = "";
    std::cin >> command;
    auto it = functions.find(command);
    if (it != functions.end() && !command.empty()) {
      it->second();
    }
    else {
      commands.printInvalidCommand();
    }
  }
  inputFile.close();
  return 0;
}
