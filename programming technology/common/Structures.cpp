#include "Structures.h"
#include <string>
#include <iostream>
#include <cctype>

oleynikova::DelimeterIO::DelimeterIO(char exp):
  exp_(exp)
{}

oleynikova::LabelIO::LabelIO(std::string label):
  label_(label)
{}

std::istream& oleynikova::operator>>(std::istream& in, DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp_ && c != std::toupper(dest.exp_))) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& oleynikova::operator>>(std::istream& in, LabelIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  std::string string = "";
  in >> string;
  if (in && (string != dest.label_)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}
