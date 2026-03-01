#include "point.h"
#include <iostream>
#include <cmath>

using namespace std;

point::point() : x(0), y(0), number(0), r(0.0) {}

point::point(int iniX, int iniY, int iniNumber)
    : x(iniX), y(iniY), number(iniNumber), r(0.0) {}

point::point(int iniX, int iniY, const point& somePoint, int iniNumber)
    : x(iniX), y(iniY), number(iniNumber)
{
    r = std::sqrt(std::pow(iniX - somePoint.x, 2) +
                  std::pow(iniY - somePoint.y, 2));
}

point::point(const point& somePoint)
    : x(somePoint.x),
      y(somePoint.y),
      number(somePoint.number),
      r(somePoint.r) {}

int point::getX() const { return x; }
int point::getY() const { return y; }
int point::getNumber() const { return number; }

void point::output() const {
    cout << "(" << x << ";" << y << ")" << endl;
}

double point::distance(const point& somePoint) const {
    return std::sqrt(std::pow(x - somePoint.x, 2) +
                     std::pow(y - somePoint.y, 2));
}

double point::getDistance() const { return r; }

bool point::compare(const point& p2) const {
    return r < p2.r;
}
