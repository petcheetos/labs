#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>
#include <iosfwd>

namespace oleynikova {

  struct DataStruct {
    long long key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
  bool operator<(const DataStruct& left, const DataStruct& right);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
}

#endif
