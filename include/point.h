#pragma once

class point
{
    int x, y, number;
    double r;
public:
    point();
    point(int iniX, int iniY, int iniNumber);
    point(int iniX, int iniY, const point& firstPoint, int iniNumber);
    point(const point& somePoint);

    int getX() const;
    int getY() const;
    int getNumber() const;
    double getR() const;

    void output() const;
    double distance(const point& somePoint) const;
    double getDistance() const;
    bool compare(const point& p2) const;
};
