#ifndef IO_FORMAT_GUARD
#define IO_FORMAT_GUARD

#include <ios>

namespace oleynikova {
  class iofmtguard {
  public:
    explicit iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
