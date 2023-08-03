#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include <utility>
#include <string>
#include <iosfwd>

namespace oleynikova {

  struct LongLongIO {
    explicit LongLongIO(long long& ref);
    long long& ref_;
  };

  struct RationalIO {
    explicit RationalIO(std::pair< long long, unsigned long long >& ref);
    std::pair< long long, unsigned long long >& ref_;
  };

  struct StringIO {
    explicit StringIO(std::string& ref);
    std::string& ref_;
  };

  std::istream& operator>>(std::istream& in, LongLongIO&& dest);
  std::istream& operator>>(std::istream& in, RationalIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
