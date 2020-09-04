#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

class Matrix : private std::vector<float>
{
public:
	Matrix(size_t rows, size_t cols);

	static Matrix createTransformation(float dx, float dy, float dz);
	static Matrix createScaling(float sx, float sy, float sz);
	static Matrix createRotationX(float rx);
	static Matrix createRotationY(float ry);
	static Matrix createRotationZ(float rz);

	float &operator()(size_t i, size_t j);
	float operator()(size_t i, size_t j) const;

	Matrix operator*(Matrix const &a) const;
	Matrix operator+(Matrix const &a) const;
	Matrix operator-(Matrix const &a) const;

	Matrix &operator*=(Matrix const &a);
	Matrix &operator+=(Matrix const &a);
	Matrix &operator-=(Matrix const &a);

	Matrix &operator*=(float t);
	Matrix &operator/=(float t);

	friend Matrix operator*(Matrix const &a, float t);
	friend Matrix operator*(float t, Matrix const &a);
	friend Matrix operator/(Matrix const &a, float t);
	friend Matrix operator/(float t, Matrix const &a);

protected:
	size_t _rows;
	size_t _cols;
};

#endif
