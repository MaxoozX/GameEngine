/**
 * File for basics geometric object (Points and Vectors)
 * @file Point.hpp
 * @author Maxence
 * @version 1.0
*/

#include <cmath>

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#define PI 3.14159

#ifndef GEOMETRY_H
#define GEOMETRY_H

namespace Geometry {

    template <class NumberType>
    class Vector;

    // Point class
    /* -------------------------------------------------------------------------------------------- */
    /** Simple class to hold a 2D Point */
    template <class NumberType>
    class Point {

        public:
            NumberType x;
            NumberType y;
            Point(NumberType _x = 0, NumberType _y = 0): x(_x), y(_y) {}
            Point<NumberType>& operator+=(Vector<NumberType> const &);
            Point<NumberType>& operator-=(Vector<NumberType> const &);

    };

    // Comparison
    /* ----------------- */
    template <class NumberType>
    bool operator==(Point<NumberType> const &p1, Point<NumberType> const &p2) {
        return (p1.x == p2.x && p1.y == p2.y);
    }

    template <class NumberType>
    bool operator!=(Point<NumberType> const &p1, Point<NumberType> const &p2) {
        return !(p1 == p2);
    }
    /* ----------------- */


    // Displaying
    /* ----------------- */
    template <class NumberType>
    std::ostream& operator<<(std::ostream& os, const Point<NumberType> p) {
        os << "P(" << p.x << ", " << p.y << ")";
        return os;
    }
    /* ----------------- */

    // Adding vector to points
    /* ----------------- */
    template <class NumberType>
    Point<NumberType>& Point<NumberType>::operator+=(Vector<NumberType> const &v) {
        x += v.x;
        y += v.y;
        return *this;
    }

    template <class NumberType>
    Point<NumberType>& Point<NumberType>::operator-=(Vector<NumberType> const &v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    /* ----------------- */
    /* -------------------------------------------------------------------------------------------- */

    // Point class
    /* -------------------------------------------------------------------------------------------- */
    /** Simple class to hold a 2D Vector */
    template <class NumberType>
    class Vector {

        public:
            NumberType x;
            NumberType y;
            Vector(NumberType _x = 0, NumberType _y = 0): x(_x), y(_y) {}

            Vector<NumberType>& operator+=(Vector<NumberType> const &);
            Vector<NumberType>& operator-=(Vector<NumberType> const &);
            Vector<NumberType>& operator*=(Vector<NumberType> const &);
            Vector<NumberType>& operator/=(Vector<NumberType> const &);
            Vector<NumberType>& operator*=(NumberType const &scalar);
            Vector<NumberType>& operator/=(NumberType const &scalar);

            NumberType euclidianNorm() const;

    };

    // In-place operations with vector
    /* ----------------- */
    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator+=(Vector<NumberType> const &v2) {
        x += v2.x;
        y += v2.y;
        return *this;
    }

    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator-=(Vector<NumberType> const &v2) {
        x -= v2.x;
        y -= v2.y;
        return *this;
    }

    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator*=(Vector<NumberType> const &v2) {
        x *= v2.x;
        y *= v2.y;
        return *this;
    }

    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator/=(Vector<NumberType> const &v2) {
        x /= v2.x;
        y /= v2.y;
        return *this;
    }
    /* ----------------- */

    // In-place operations with scalar
    /* ----------------- */
    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator*=(NumberType const &scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class NumberType>
    Vector<NumberType>& Vector<NumberType>::operator/=(NumberType const &scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    template <class NumberType>
    Vector<NumberType> operator*(Vector<NumberType> const &v1, NumberType const &scalar) {
        return Vector<NumberType>(v1.x * scalar, v1.y * scalar);
    }

    template <class NumberType>
    Vector<NumberType> operator/(Vector<NumberType> const &v1, NumberType const &scalar) {
        return Vector<NumberType>(v1.x / scalar, v1.y / scalar);
    }
    /* ----------------- */

    // Binary operations
    /* ----------------- */
    template <class NumberType>
    Vector<NumberType> operator+(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return Vector<NumberType>(v1.x + v2.x, v1.y + v2.y);
    }

    template <class NumberType>
    Vector<NumberType> operator-(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return Vector<NumberType>(v1.x - v2.x, v1.y - v2.y);
    }

    template <class NumberType>
    Vector<NumberType> operator*(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return Vector<NumberType>(v1.x * v2.x, v1.y * v2.y);
    }

    template <class NumberType>
    Vector<NumberType> operator/(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return Vector<NumberType>(v1.x / v2.x, v1.y / v2.y);
    }
    /* ----------------- */

    // Unary minus (-)
    /* ----------------- */
    template <class NumberType>
    Vector<NumberType> operator-(Vector<NumberType> const &v) {
        return Vector<NumberType>(-v.x, -v.y);
    }
    /* ----------------- */

    // Comparison
    /* ----------------- */
    template <class NumberType>
    bool operator==(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return (v1.x == v2.x && v1.y == v2.y);
    }

    template <class NumberType>
    bool operator!=(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
        return !(v1 == v2);
    }
    /* ----------------- */

    // Displaying vector
    /* ----------------- */
    template <class NumberType>
    std::ostream& operator<<(std::ostream& os, const Vector<NumberType> p) {
        os << "V(" << p.x << ", " << p.y << ")";
        return os;
    }
    /* ----------------- */

    // Useful functions
    /* ----------------- */
    template <class NumberType>
    NumberType Vector<NumberType>::euclidianNorm() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    template <class NumberType>
    NumberType DotProduct(const Vector<NumberType> &a, const Vector<NumberType> &b) {
        return ((a.x * b.x) + (a.y * b.y));
    }

    template <class NumberType>
    NumberType CrossProduct(const Vector<NumberType> &a, const Vector<NumberType> &b) {
        return ((a.x * b.y) - (a.y * b.x));
    }
    /* ----------------- */

    // Polygon class
    /* -------------------------------------------------------------------------------------------- */
    /** A class to store a polygon, stores the vertices and then can compute center, side and diagonals */
    template <class NumberType>
    class Polygon {

        public:
            std::vector<Point<NumberType> > vertices; // Must be at least 3 vertices
            Point<NumberType> midPoint;
            std::vector<std::pair<Point<NumberType>, Point<NumberType> > > sides;
            std::vector<std::pair<Point<NumberType>, Point<NumberType> > > diagonals;
            Polygon() {}
            bool checkValidity();
            void computeMidPoint();
            void computeSidesAndDiagonals();
    };

    // Useful functions
    /* ----------------- */
    template <class NumberType>
    bool Polygon<NumberType>::checkValidity() {
        return (vertices.size() >= 3);
    }

    template <class NumberType>
    void Polygon<NumberType>::computeMidPoint() {

        NumberType minX, maxX, minY, maxY, curX, curY;
        minX = vertices[0].x;
        maxX = vertices[0].x;
        minY = vertices[0].y;
        maxY = vertices[0].y;

        for(int index = 1; index < vertices.size(); index++) {
            curX = vertices[index].x;
            curY = vertices[index].y;

            if(curX > maxX) maxX = curX;
            else if(curX < minX) minX = curX;

            if(curY > maxY) maxY = curY;
            else if(curY < minY) minY = curY;
        }

        midPoint.x = minX + (maxX - minX) / 2;
        midPoint.y = minY + (maxY - minY) / 2;

        // Sort the vertices in clockwise order so that we can join them and create sides
        std::sort(vertices.begin(), vertices.end(), [&](Point<NumberType> p1, Point<NumberType> p2) {
            return ((p1.x - midPoint.x) * (p2.y - midPoint.y) - (p2.x - midPoint.x) * (p1.y - midPoint.y) > 0);
        });

    }

    // Always call computeMidPoint before this method
    template <class NumberType>
    void Polygon<NumberType>::computeSidesAndDiagonals() {
        for(int index = 0; index < vertices.size(); index++) {
            sides.push_back(std::make_pair(vertices[index], vertices[(index+1)%vertices.size()]));
            diagonals.push_back(std::make_pair(midPoint, vertices[(index+1)%vertices.size()]));
        }
    }
    /* ----------------- */

    template <class NumberType>
    std::pair<bool, Point<NumberType>* > checkLineCollision(std::pair<Point<NumberType>, Point<NumberType> > line1, std::pair<Point<NumberType>, Point<NumberType> > line2) {

        /*
        The algorithm consits of 3 steps

        1.  If the lines are parrallels -> False
        2.  Find the point where the 2 lines would cross if they were infinite
        3.  If the point does not belong to any of the 2 lines -> False
            Else the lines are colliding, their collision point exists.

        */

        double deltaX1 = line1.second.x - line1.first.x;
        double deltaY1 = line1.second.y - line1.first.y;
        double slope1 = deltaY1 / deltaX1;
        double offset1 = line1.first.y - (line1.first.x * slope1);

        double deltaX2 = line2.second.x - line2.first.x;
        double deltaY2 = line2.second.y - line2.first.y;
        double slope2 = deltaY2 / deltaX2;
        double offset2 = line2.first.y - (line2.first.x * slope2);

        // 1.
        if(slope2 == slope1) {
            return std::make_pair(false, nullptr);
        }

        // 2.
        double intersectionX = (offset2 - offset1) / (slope1 - slope2);

        int line1minX = std::min(line1.first.x, line1.second.x);
        int line1maxX = std::max(line1.first.x, line1.second.x);
        int line2minX = std::min(line2.first.x, line2.second.x);
        int line2maxX = std::max(line2.first.x, line2.second.x);

        if(line1minX <= intersectionX && intersectionX <= line1maxX && line2minX <= intersectionX && intersectionX <= line2maxX) {
            return std::make_pair(true, new Point<NumberType>(intersectionX, slope1 * intersectionX + offset1));
        }

        return std::make_pair(false, nullptr);

    }

    template <class NumberType>
    std::pair<bool, Point<NumberType>* > checkPolygonCollision(Polygon<NumberType> polygon1, Polygon<NumberType> polygon2) {

        for(auto side: polygon1.sides) {
            for(auto diagonal: polygon2.diagonals) {
                std::pair<bool, Point<NumberType>* > result = checkLineCollision(side, diagonal);
                if(result.first) {
                    return result;
                }
            }
        }

        for(auto side: polygon2.sides) {
            for(auto diagonal: polygon1.diagonals) {
                std::pair<bool, Point<NumberType>* > result = checkLineCollision(side, diagonal);
                if(result.first) {
                    return result;
                }
            }
        }

        return std::make_pair(false, nullptr);

    }
}
#endif // GEOMETRY_H