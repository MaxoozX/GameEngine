/**
 * File for basics geometric object (Points and Vectors)
 * @file Point.hpp
 * @author Maxence
 * @version 1.0
*/

#include <cmath>

#include <iostream>

#ifndef GEOMETRY_H
#define GEOMETRY_H

template <class NumberType>
class Vector;

/* -------------------------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------------------------- */

/** Simple class to hold a 2D Point */
template <class NumberType>
class Point {

    public:
        NumberType x;
        NumberType y;
        Point(NumberType _x = 0, NumberType _y = 0): x(_x), y(_y) {}
        Point<NumberType>& operator+=(Point<NumberType> const &);
        Point<NumberType>& operator-=(Point<NumberType> const &);
        Point<NumberType>& operator+=(Vector<NumberType> const &);
        Point<NumberType>& operator-=(Vector<NumberType> const &);

};

template <class NumberType>
bool operator==(Point<NumberType> const &p1, Point<NumberType> const &p2) {
    return (p1.x == p2.x && p1.y == p2.y);
}

template <class NumberType>
bool operator!=(Point<NumberType> const &p1, Point<NumberType> const &p2) {
    return !(p1 == p2);
}

template <class NumberType>
std::ostream& operator<<(std::ostream& os, const Point<NumberType> p) {
    os << "P(" << p.x << ", " << p.y << ")";
    return os;
}

/* -------------------------------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------------------------------- */

// The opposite vector's method
template <class NumberType>
Point<NumberType>& Point<NumberType>::operator+=(Vector<NumberType> const &v) {

}

template <class NumberType>
Point<NumberType>& Point<NumberType>::operator-=(Vector<NumberType> const &v) {

}

template <class NumberType>
Vector<NumberType> operator+(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
    return Vector<NumberType>(v1.x + v2.x, v1.y + v2.y);
}

template <class NumberType>
Vector<NumberType> operator-(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
    return Vector<NumberType>(v1.x - v2.x, v1.y - v2.y);
}

/* -------------------------------------------------------------------------------------------- */

// In-place operations: += -= *= /= for vectors with vectors
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

/* ----------------------------------------------- */

// Operations with scalars

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

/* -------------------------------------------------------------------------------------------- */

// 4 operations: + - * /

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

/* -------------------------------------------------------------------------------------------- */

// Unary minus (-)
template <class NumberType>
Vector<NumberType> operator-(Vector<NumberType> const &v) {
    return Vector<NumberType>(-v.x, -v.y);
}

/* -------------------------------------------------------------------------------------------- */

// Equality operations

template <class NumberType>
bool operator==(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
    return (v1.x == v2.x && v1.y == v2.y);
}

template <class NumberType>
bool operator!=(Vector<NumberType> const &v1, Vector<NumberType> const &v2) {
    return !(v1 == v2);
}

/* -------------------------------------------------------------------------------------------- */

// Displaying Vector on console
template <class NumberType>
std::ostream& operator<<(std::ostream& os, const Vector<NumberType> p) {
    os << "V(" << p.x << ", " << p.y << ")";
    return os;
}

/* -------------------------------------------------------------------------------------------- */

// Named functions 
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

#endif // GEOMETRY_H