#include "Commands.h"
#include <iosfwd>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <limits>
#include <iterator>
#include <IOFormatGuard.h>

oleynikova::Commands::Commands(std::ostream& ostream, std::istream& istream) :
  ostream_(ostream),
  istream_(istream)
{}

void oleynikova::Commands::inputData(std::istream& in)
{
  while (!in.eof()) {
    in.clear();
    std::copy(std::istream_iterator< Polygon >(in), std::istream_iterator< Polygon >(), std::back_inserter(storage_));
  }
}

void oleynikova::Commands::doArea()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  std::string param;
  istream_ >> param;
  double sum = 0.0;
  if ((!param.compare("EVEN")) || (!param.compare("ODD"))) {
    bool isEven = (!param.compare("EVEN")) ? true : false;
    sum = getAreaOddEven(storage_, isEven);
    ostream_ << std::fixed << std::setprecision(1) << sum << "\n";
  }
  else if (!param.compare("MEAN")) {
    if (storage_.empty()) {
      printInvalidCommand();
      return;
    }
    ostream_ << std::fixed << std::setprecision(1) << getAreaMean(storage_) / storage_.size() << "\n";
  }
  else if (std::all_of(param.begin(), param.end(), [](char c) {return isdigit(c); })) {
    size_t count = std::stoul(param);
    if (count < 3) {
      printInvalidCommand();
      return;
    }
    sum = getAreaNum(count, storage_);
    ostream_ << std::fixed << std::setprecision(1) << sum << "\n";
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::doMax()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  std::string param;
  istream_ >> param;
  if (storage_.empty()) {
    printInvalidCommand();
    return;
  }
  if (!param.compare("AREA")) {
    ostream_ << std::fixed << std::setprecision(1) << getAreaMax(storage_) << "\n";
  }
  else if (!param.compare("VERTEXES")) {
    ostream_ << std::fixed << std::setprecision(1) << getMaxVertexes(storage_) << "\n";
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::doMin()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  std::string param;
  istream_ >> param;
  if (storage_.empty()) {
    printInvalidCommand();
    return;
  }
  if (!param.compare("AREA")) {
    ostream_ << std::fixed << std::setprecision(1) << getAreaMin(storage_) << "\n";
  }
  else if (!param.compare("VERTEXES")) {
    ostream_ << std::fixed << std::setprecision(1) << getMinVertexes(storage_) << "\n";
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::doCount()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  std::string param;
  istream_ >> param;
  if (!param.compare("EVEN") || !param.compare("ODD")) {
    bool isEven = (!param.compare("EVEN")) ? true : false;
    ostream_ << countOddEven(storage_, isEven) << "\n";
  }
  else if (std::all_of(param.begin(), param.end(), [](char c) {return isdigit(c); })) {
    size_t number = std::stoul(param);
    if (number < 3) {
      printInvalidCommand();
      return;
    }
    else {
      ostream_ << countNum(number, storage_) << "\n";
    }
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::doMaxSeq()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  Polygon inputPolygon;
  istream_ >> inputPolygon;
  if (istream_.rdstate() == std::ios_base::failbit) {
    printInvalidCommand();
    istream_.clear();
    return;
  }
  size_t count = 0;
  size_t maxCount = 0;
  for (const Polygon& polygon : storage_) {
    if (polygon == inputPolygon) {
      count++;
    }
    else {
      maxCount = std::max(maxCount, count);
      count = 0;
    }
  }
  ostream_ << maxCount << "\n";
}

void oleynikova::Commands::doRightShapes()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  if (!storage_.empty()) {
    ostream_ << countRightShapes(storage_) << "\n";
  }
  else {
    printInvalidCommand();
  }
}

void oleynikova::Commands::printInvalidCommand()
{
  oleynikova::iofmtguard fmtguard(ostream_);
  istream_.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  ostream_ << "<INVALID COMMAND>" << "\n";
}

double oleynikova::getAreaOddEven(const std::vector< oleynikova::Polygon >& storage, bool parity)
{
  return std::accumulate(storage.begin(), storage.end(), 0.0,
    [parity](double acc, const Polygon& polygon) {
    return (parity == (polygon.countVertex() % 2 == 0)) ? acc + polygon.getArea() : acc;
  });
}

double oleynikova::getAreaMean(const std::vector< oleynikova::Polygon >& storage)
{
  return std::accumulate(storage.begin(), storage.end(), 0.0,
    [](double acc, const Polygon& polygon) {
    return acc + polygon.getArea();
  });
}

double oleynikova::getAreaNum(size_t number, const std::vector< oleynikova::Polygon >& storage)
{
  return std::accumulate(storage.begin(), storage.end(), 0.0,
    [number](double acc, const Polygon& polygon) {
    return (polygon.countVertexes == number) ? acc + polygon.getArea() : acc;
  });
}

double oleynikova::getAreaMin(const std::vector< oleynikova::Polygon >& storage)
{
  auto minAreaPolygon = std::min_element(storage.begin(), storage.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.getArea() < p2.getArea();
  });
  return minAreaPolygon->getArea();
}

double oleynikova::getAreaMax(const std::vector< oleynikova::Polygon >& storage)
{
  auto maxAreaPolygon = std::max_element(storage.begin(), storage.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.getArea() < p2.getArea();
  });
  return maxAreaPolygon->getArea();
}

size_t oleynikova::countOddEven(const std::vector< oleynikova::Polygon >& storage, bool parity)
{
  return std::count_if(storage.begin(), storage.end(),
    [parity](const Polygon& polygon) {
    return ((polygon.countVertexes % 2 == 0) == parity);
  });
}

size_t oleynikova::countNum(size_t number, const std::vector< oleynikova::Polygon >& storage)
{
  return std::count_if(storage.begin(), storage.end(),
    [&number](const Polygon& polygon) {
    return (polygon.countVertex() == number);
  });
}

size_t oleynikova::getMinVertexes(const std::vector< oleynikova::Polygon >& storage)
{
  auto minVertexesPolygon = std::min_element(storage.begin(), storage.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.countVertex() < p2.countVertex();
  });
  return minVertexesPolygon->countVertex();
}

size_t oleynikova::getMaxVertexes(const std::vector< oleynikova::Polygon >& storage)
{
  auto maxVertexesPolygon = std::max_element(storage.begin(), storage.end(),
    [](const Polygon& p1, const Polygon& p2) {
    return p1.countVertex() < p2.countVertex();
  });
  return maxVertexesPolygon->countVertex();
}

size_t oleynikova::countRightShapes(const std::vector< oleynikova::Polygon >& storage)
{
  return std::count_if(storage.begin(), storage.end(),
    [](const Polygon& polygon) {
    return polygon.checkRightAngle();
  });
}
