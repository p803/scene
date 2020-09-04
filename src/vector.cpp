#include "vector.hpp"

#include <cmath>

Vector::Vector(Matrix const &a) : Vector(a(0, 0), a(0, 1), a(0, 2))
{
}

Vector::Vector(float x, float y, float z) : Matrix(1, 4)
{
	(*this)(0, 0) = x;
	(*this)(0, 1) = y;
	(*this)(0, 2) = z;
	(*this)(0, 3) = 0;
}

Vector Vector::unitise() const
{
	return resize(1);
}

Vector Vector::resize(float desiredLength) const
{
	float t = desiredLength / length();

	return *this * t;
}

Vector Vector::revert() const
{
	return *this * -1;
}

float Vector::length() const
{
	return std::sqrt(dot(*this));
}

float Vector::dot(Vector const &u) const
{
	return x() * u.x() + y() * u.y() + z() * u.z();
}

Vector Vector::cross(Vector const &u) const
{
	return Vector(
		y() * u.z() - z() * u.y(),
		z() * u.x() - x() * u.z(),
		x() * u.y() - y() * u.x());
}

Vector Vector::rebase(Vector const &bx, Vector const &by, Vector const &bz) const
{
	return Vector(
		x() * bx.x() + y() * by.x() + z() * bz.x(),
		x() * bx.y() + y() * by.y() + z() * bz.y(),
		x() * bx.z() + y() * by.z() + z() * bz.z());
}

float Vector::x() const
{
	return (*this)(0, 0);
}

float Vector::y() const
{
	return (*this)(0, 1);
}

float Vector::z() const
{
	return (*this)(0, 2);
}
