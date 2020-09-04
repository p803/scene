#include "point.hpp"

#include "ray.hpp"

Point::Point(float x, float y, float z) : Matrix(1, 4)
{
	(*this)(0, 0) = x;
	(*this)(0, 1) = y;
	(*this)(0, 2) = z;
	(*this)(0, 3) = 0;
}

Point::Point(Matrix const &a) : Point(a(0, 0), a(0, 1), a(0, 2))
{
}

Point Point::rebase(Point const &origin) const
{
	return origin.vectorTo(*this);
}

Vector Point::vectorTo(Point const &target) const
{
	return Vector(target.x() - x(), target.y() - y(), target.z() - z());
}

Vector Point::directionTo(Point const &target) const
{
	return vectorTo(target).unitise();
}

float Point::distanceTo(Point const &target) const
{
	return vectorTo(target).length();
}

Ray Point::rayTo(Point const &target) const
{
	return Ray(*this, directionTo(target));
}

float Point::x() const
{
	return (*this)(0, 0);
}

float Point::y() const
{
	return (*this)(0, 1);
}

float Point::z() const
{
	return (*this)(0, 2);
}
