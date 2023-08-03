#include "SortingTester.h"
#include <random>

int oleynikova::generateRandomNumber(const int min, const int max)
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution< int > dist(min, max);
  return dist(mt);
}

float oleynikova::generateRandomNumber(const float min, const float max)
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution< float > dist(min, max);
  return dist(mt);
}
