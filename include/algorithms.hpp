#include "math/Vector3.hpp"
#include <vector>

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

namespace t {

std::vector<std::pair<int, int>> bresenhamLow(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int yIncrement = 1;
  if (dy < 0) {
    yIncrement = -1;
    dy *= -1;
  }
  int difference = 2 * dy - dx;
  int y = y0;

  std::vector<std::pair<int, int>> points;

  for (int x = x0; x <= x1; ++x) {
    points.push_back(std::make_pair(x, y));

    if (difference > 0) {
      y += yIncrement;
      difference += 2 * (dy - dx);
    } else {
      difference += 2 * dy;
    }
  }

  return points;
}

std::vector<std::pair<int, int>> bresenhamHigh(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0;
  int dy = y1 - y0;
  int xIncrement = 1;
  if (dx < 0) {
    xIncrement = -1;
    dx *= -1;
  }
  int difference = 2 * dx - dy;
  int x = x0;

  std::vector<std::pair<int, int>> points;

  for (int y = y0; y <= y1; ++y) {
    points.push_back(std::make_pair(x, y));

    if (difference > 0) {
      x += xIncrement;
      difference += 2 * (dx - dy);
    } else {
      difference += 2 * dx;
    }
  }

  return points;
}

std::vector<std::pair<int, int>> bresenham(int x0, int y0, int x1, int y1) {
  if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
    if (x0 > x1) {
      return bresenhamLow(x1, y1, x0, y0);
    } else {
      return bresenhamLow(x0, y0, x1, y1);
    }
  } else {
    if (y0 > y1) {
      return bresenhamHigh(x1, y1, x0, y0);
    } else {
      return bresenhamHigh(x0, y0, x1, y1);
    }
  }
}

Vector3 barycentric(Vector3 point, Vector3 vertexA, Vector3 vertexB,
                    Vector3 vertexC) {
  Vector3 edgeAB = vertexB - vertexA;
  Vector3 edgeAC = vertexC - vertexA;
  Vector3 ap = point - vertexA;

  double dotABAB = Vector3::dot(edgeAB, edgeAB);
  double dotABAC = Vector3::dot(edgeAB, edgeAC);
  double dotACAC = Vector3::dot(edgeAC, edgeAC);
  double dotAPAB = Vector3::dot(ap, edgeAB);
  double dotAPAC = Vector3::dot(ap, edgeAC);
  double denominator = dotABAB * dotACAC - dotABAC * dotABAC;

  double v = (dotACAC * dotAPAB - dotABAC * dotAPAC) / denominator;
  double w = (dotABAB * dotAPAC - dotABAC * dotAPAB) / denominator;
  double u = 1.0 - v - w;

  return Vector3(u, v, w);
}

} // namespace t

#endif // ALGORITHMS_HPP