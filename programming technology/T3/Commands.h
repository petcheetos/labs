#ifndef COMMANDS_H
#define COMMANDS_H

#include <vector>
#include <iosfwd>
#include <functional>
#include <string>
#include <map>
#include "Figures.h"

namespace oleynikova {
  class Commands {
  public:
    Commands(std::ostream& ostream, std::istream& istream);
    ~Commands() = default;
    void inputData(std::istream& in);
    void doArea();
    void doMax();
    void doMin();
    void doCount();
    void doMaxSeq();
    void doRightShapes();
    void printInvalidCommand();

  private:
    std::ostream& ostream_;
    std::istream& istream_;
    std::vector < Polygon > storage_;
  };

  double getAreaOddEven(const std::vector< oleynikova::Polygon >& storage, bool parity);
  double getAreaMean(const std::vector< oleynikova::Polygon >& storage);
  double getAreaNum(size_t number, const std::vector< oleynikova::Polygon >& storage);
  double getAreaMin(const std::vector< oleynikova::Polygon >& storage);
  double getAreaMax(const std::vector< oleynikova::Polygon >& storage);
  size_t countOddEven(const std::vector< oleynikova::Polygon >& storage, bool parity);
  size_t countNum(size_t number, const std::vector< oleynikova::Polygon >& storage);
  size_t getMinVertexes(const std::vector< oleynikova::Polygon >& storage);
  size_t getMaxVertexes(const std::vector< oleynikova::Polygon >& storage);
  size_t countRightShapes(const std::vector< oleynikova::Polygon >& storage);
}

#endif
