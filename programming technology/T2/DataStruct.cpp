#include "DataStruct.h"
#include <iomanip>
#include <IOFormatGuard.h>
#include <Structures.h>
#include "DataStructures.h"

bool oleynikova::operator<(const DataStruct& left, const DataStruct& right)
{
  if (left.key1 != right.key1) {
    return left.key1 < right.key1;
  }
  else {
    if (left.key2 != right.key2) {
      return left.key2 < right.key2;
    }
    else {
      return left.key3.size() < right.key3.size();
    }
  }
}

std::ostream& oleynikova::operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  oleynikova::iofmtguard fmtguard(out);
  out << "(" << ":key1 " << dest.key1 << "ll";
  out << ":key2 " << "(:N " << dest.key2.first << ":D " << dest.key2.second << ":)";
  out << ":key3 \"" << dest.key3 << "\"" << ":)";
  return out;
}

std::istream& oleynikova::operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct inputData;
  std::string inputKey;
  in >> DelimeterIO{'('} >> DelimeterIO{':'};
  for (size_t i = 0; i < 3; i++) {
    in >> inputKey;
    if (inputKey == "key1") {
      in >> LongLongIO{ inputData.key1 };
    }
    else if (inputKey == "key2") {
      in >> RationalIO{ inputData.key2 };
    }
    else if (inputKey == "key3") {
      in >> StringIO{ inputData.key3 };
    }
    else {
      in.setstate(std::ios::failbit);
    }
    in >> DelimeterIO{':'};
  }
  in >> DelimeterIO{')'};
  if (in) {
    dest = inputData;
  }
  return in;
}
