#pragma once

/**
 * @brief Represents a point on a 2D plane and distance between points
 */
class point
{
    int x, y, number;
    double r;
public:
    /**
     * @brief Creates a point at the (0;0) with number 0
     */
    point();

    /**
     * @brief Creates a point with given coordinates with distance 0
     * @param iniX X coordinate
     * @param iniY Y coordinate
     * @param iniNumber Point index
     */
    point(int iniX, int iniY, int iniNumber);

    /**
     * @brief Creates a point with given coordinates and with distance to other point
     * @param iniX X coordinate
     * @param iniY Y coordinate
     * @param somePoint Other point to calculate distance 
     * @param iniNumber Point index
     */
    point(int iniX, int iniY, const point& somePoint, int iniNumber);

    /**
     * @brief Copy another point
     */
    point(const point& somePoint);

    /**
     * @brief Returns X coordinate
     */
    int getX() const;

    /**
     * @brief Return Y coordinate
     */
    int getY() const;

    /**
     * @brief Return index of point
     */
    int getNumber() const;

    /**
     * @brief Prints point coordinates as (x;y)
     */
    void output() const;

    /**
     * @brief Calculate distance between this point and other point
     * @param somePoint other point
     */
    double distance(const point& somePoint) const;

    /**
     * @brief Return distance
     */
    double getDistance() const;

    /**
     * @brief Compare distances of two points
     * @param p2 Other point
     * @return True if this point < other point
     */
    bool compare(const point& p2) const;
};
