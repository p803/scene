#include "matrix.hpp"

#include <math.h>

Matrix::Matrix(size_t rows, size_t cols) : std::vector<float>(rows * cols), _rows(rows), _cols(cols)
{
}

Matrix Matrix::createTransformation(float dx, float dy, float dz)
{
	Matrix a(4, 4);

	a(0, 0) = a(1, 1) = a(2, 2) = a(3, 3) = 1;
	a(0, 3) = dx;
	a(1, 3) = dy;
	a(2, 3) = dz;

	return a;
}

Matrix Matrix::createScaling(float sx, float sy, float sz)
{
	Matrix a(4, 4);

	a(0, 0) = sx;
	a(1, 1) = sy;
	a(2, 2) = sz;
	a(3, 3) = 1;

	return a;
}

Matrix Matrix::createRotationX(float rx)
{
	Matrix a(4, 4);

	a(0, 0) = a(3, 3) = 1;
	a(1, 1) = a(2, 2) = cos(rx);
	a(1, 2) = -(a(2, 1) = sin(rx));

	return a;
}

Matrix Matrix::createRotationY(float ry)
{
	Matrix a(4, 4);

	a(0, 0) = a(2, 2) = cos(ry);
	a(1, 1) = a(3, 3) = 1;
	a(2, 0) = -(a(0, 2) = sin(ry));

	return a;
}

Matrix Matrix::createRotationZ(float rz)
{
	Matrix a(4, 4);

	a(0, 0) = a(1, 1) = cos(rz);
	a(0, 1) = -(a(1, 0) = sin(rz));
	a(2, 2) = a(3, 3) = 1;

	return a;
}

float &Matrix::operator()(size_t i, size_t j)
{
	return (*this)[i * _cols + j];
}

float Matrix::operator()(size_t i, size_t j) const
{
	return (*this)[i * _cols + j];
}

Matrix Matrix::operator*(const Matrix &a) const
{
	Matrix r(*this);

	return r *= a;
}

Matrix &Matrix::operator*=(const Matrix &a)
{
	if (_cols != a._rows)
	{
		throw "Exception in Matrix::operator*(): incompatible size.\n";
	}

	for (size_t i = 0; i < _rows; ++i)
	{
		for (size_t j = 0; j < _cols; ++j)
		{
			float x = 0;

			for (size_t k = 0; k < _rows; ++k)
			{
				x += (*this)(i, k) * a(k, j);
			}

			(*this)(i, j) = x;
		}
	}

	return *this;
}

Matrix Matrix::operator+(Matrix const &a) const
{
	Matrix r(*this);

	return r += a;
}

Matrix &Matrix::operator+=(Matrix const &a)
{
	if (_cols != a._cols || _rows != a._rows)
	{
		throw "Exception in Matrix::operator+=(): incompatible size.\n";
	}

	for (size_t i = 0; i < _rows; ++i)
	{
		for (size_t j = 0; j < _cols; ++j)
		{
			(*this)(i, j) += a(i, j);
		}
	}

	return *this;
}

Matrix Matrix::operator-(Matrix const &a) const
{
	Matrix r(*this);

	return r -= a;
}

Matrix &Matrix::operator-=(Matrix const &a)
{
	return (*this) += a * -1;
}

Matrix &Matrix::operator*=(float t)
{
	for (size_t i = 0; i < _rows; ++i)
	{
		for (size_t j = 0; j < _cols; ++j)
		{
			(*this)(i, j) *= t;
		}
	}

	return *this;
}

Matrix &Matrix::operator/=(float t)
{
	return (*this) *= 1 / t;
}

Matrix operator*(Matrix const &a, float t)
{
	Matrix r(a);

	return r *= t;
}

Matrix operator/(Matrix const &a, float t)
{
	Matrix r(a);

	return r /= t;
}

Matrix operator*(float t, Matrix const &a)
{
	Matrix r(a);

	return r *= t;
}

Matrix operator/(float t, Matrix const &a)
{
	Matrix r(a);

	return r /= t;
}
