#include "Figures.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <limits>
#include <typeinfo>
#include <Structures.h>

std::istream& oleynikova::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return in >> DelimeterIO{ '(' } >> point.x >> DelimeterIO{ ';' } >> point.y >> DelimeterIO{ ')' };
}

bool oleynikova::operator==(const Point& left, const Point& right)
{
  if ((left.x == right.x) && (left.y == right.y)) {
    return true;
  }
  return false;
}

bool oleynikova::isRightAngle(const Point& first, const Point& second, const Point& third)
{
  return (((second.x - first.x) * (third.x - second.x) + (third.y - second.y) * (second.y - first.y)) == 0);
}

double oleynikova::Polygon::getArea() const
{
  std::vector< double > areas;
  std::vector < Point > copyPoints = points;
  copyPoints.push_back(points[0]);
  std::transform(copyPoints.begin(), copyPoints.end() - 1, copyPoints.begin() + 1, std::back_inserter(areas),
    [&areas](const Point& left, const Point& right)
  {
    double temp = (left.x + right.x) * (right.y - left.y);
    return temp;
  });
  double area = std::abs(0.5 * std::accumulate(areas.begin(), areas.end(), 0.0));
  return area;
}

size_t oleynikova::Polygon::countVertex() const
{
  return countVertexes;
}

bool oleynikova::Polygon::checkRightAngle() const
{
  if (oleynikova::isRightAngle(points[0], points[countVertexes - 1], points[countVertexes - 2])) {
    return true;
  }
  if (oleynikova::isRightAngle(points[countVertexes - 1], points[0], points[1])) {
    return true;
  }
  return false;
}

bool oleynikova::Polygon::isSame(Polygon& other) const
{
  return std::equal(points.begin(), points.end(), other.points.begin());
}

bool oleynikova::operator==(const Polygon& left, const Polygon& right)
{
  if (left.points == right.points) {
    return true;
  }
  return false;
}

std::istream& oleynikova::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Polygon inputPolygon;
  size_t count;
  in >> count;
  std::copy_if(std::istream_iterator< Point >(in), std::istream_iterator< Point >(), std::back_inserter(inputPolygon.points),
    [&in](const Point& point) {
    if ((in.eof()) || (in.peek() == '\n')) {
      in.setstate(std::ios_base::eofbit);
    }
    return (typeid(point.x) == typeid(int));
  });
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  if ((count < 3) || (count != inputPolygon.points.size())) {
    in.setstate(std::ios::failbit);
  }
  else {
    polygon.points = inputPolygon.points;
    polygon.countVertexes = inputPolygon.points.size();
  }
  return in;
}
