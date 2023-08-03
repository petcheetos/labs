#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <string>
#include <functional>
#include <limits>
#include <map>
#include "HuffmanCoding.h"

namespace oleynikova {
  class Commands {
  public:
    Commands(std::istream& in, std::ostream& out);
    ~Commands() = default;
    void printInfo();
    void inputData();
    void unite();
    void printHuffmanEncodeResult();
    void printInvalidCommand();
    void inputCommand(int& exit);
    void inputUserData();

    std::string getSourceData();
    std::string getResultData();

  private:
    std::istream& istream;
    std::ostream& ostream;
    std::map< std::string, std::function< void() > > functions;
    std::string source;
    std::string result;
  };
}

#endif
