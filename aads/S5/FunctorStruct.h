#ifndef FUNCTOR_STRUCT_H
#define FUNCTOR_STRUCT_H

#include <string>
#include <utility>

namespace oleynikova {
  struct NodeSumm {
    NodeSumm();
    void operator()(const std::pair< int, std::string >& node);

    int keyResult;
    std::string stringResult;
  };
}

#endif
