#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <iosfwd>

namespace oleynikova {

  struct DelimeterIO {
    explicit DelimeterIO(char exp);
    char exp_;
  };

  struct LabelIO {
    explicit LabelIO(std::string label);
    std::string label_;
  };

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest);
  std::istream& operator>>(std::istream& in, LabelIO&& dest);
}

#endif
