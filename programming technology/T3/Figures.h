#ifndef FIGURES_H
#define FIGURES_H

#include <iosfwd>
#include <vector>

namespace oleynikova {
  struct Point {
    int x, y;
  };
  struct Polygon {
    double getArea() const;
    size_t countVertex() const;
    bool checkRightAngle() const;
    bool isSame(Polygon& other) const;

    std::vector< oleynikova::Point > points;
    size_t countVertexes;
  };

  std::istream &operator>>(std::istream& in, Point& point);
  bool operator==(const Point& left, const Point& right);

  bool isRightAngle(const Point& first, const Point& second, const Point& third);
  bool operator==(const Polygon& left, const Polygon& right);
  std::istream &operator>>(std::istream& in, Polygon& polygon);
}

#endif
