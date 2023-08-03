#include "IOFormatGuard.h"
#include <ios>

oleynikova::iofmtguard::iofmtguard(std::basic_ios< char >& s):
  s_(s),
  fill_(s.fill()),
  fmt_(s.flags())
{}

oleynikova::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.flags(fmt_);
}
