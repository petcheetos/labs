#include "DataStructures.h"
#include <utility>
#include <string>
#include <iostream>
#include <cctype>
#include <Structures.h>

oleynikova::LongLongIO::LongLongIO(long long& ref):
  ref_(ref)
{}

oleynikova::RationalIO::RationalIO(std::pair< long long, unsigned long long >& ref):
  ref_(ref)
{}

oleynikova::StringIO::StringIO(std::string& ref):
  ref_(ref)
{}

std::istream& oleynikova::operator>>(std::istream& in, LongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> dest.ref_ >> DelimeterIO{'l'} >> DelimeterIO{'l'};
}

std::istream& oleynikova::operator>>(std::istream& in, RationalIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  in >> DelimeterIO{'('} >> LabelIO{":N"} >> dest.ref_.first;
  in >> LabelIO{":D"} >> dest.ref_.second >> DelimeterIO{':'} >> DelimeterIO{')'};
  return in;
}

std::istream& oleynikova::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimeterIO{'"'}, dest.ref_, '"');
}
