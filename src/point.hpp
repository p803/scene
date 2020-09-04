#ifndef POINT_HPP
#define POINT_HPP

class Vector;
class Ray;

#include "matrix.hpp"

class Point : public Matrix
{
public:
	Point(Matrix const &a);
	Point(float x, float y, float z);

	Vector vectorTo(Point const &target) const;
	Vector directionTo(Point const &target) const;
	float distanceTo(Point const &target) const;
	Ray rayTo(Point const &target) const;
	Point rebase(Point const &origin) const;

	float x() const;
	float y() const;
	float z() const;
};

#endif
