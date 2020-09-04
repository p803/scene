#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"

class Vector : public Matrix
{
public:
	Vector(Matrix const &a);
	Vector(float x, float y, float z);

	Vector unitise() const;
	Vector resize(float desiredLength) const;
	Vector revert() const;
	float length() const;

	float dot(Vector const &u) const;
	Vector cross(Vector const &u) const;
	Vector rebase(Vector const &x, Vector const &y, Vector const &z) const;

	float x() const;
	float y() const;
	float z() const;
};

#endif
