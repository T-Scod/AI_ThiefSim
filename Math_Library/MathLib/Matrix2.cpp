#include "Matrix2.h"
#include <math.h>

//sets default values for the matrix
Matrix2::Matrix2()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			//since the array is in union with the coordinates both the array and the coordinates will become 0
			data[i][j] = 0.0f;
		}
	}
}
//allows specific values to be set for the matrix elements
Matrix2::Matrix2(const float Xx, const float Xy, const float Yx, const float Yy)
{
	data[0][0] = Xx; data[1][0] = Yx;
	data[0][1] = Xy; data[1][1] = Yy;
}
//allows specific vectors to be set for the axis
Matrix2::Matrix2(const Vector2 X, const Vector2 Y)
{
	xAxis = X;
	yAxis = Y;
}
Matrix2::~Matrix2()
{
}

//contains the identity matrix for a matrix 2
const Matrix2 Matrix2::identity = Matrix2(1, 0, 0, 1);

//allows for iteration of the array
Vector2 & Matrix2::operator[](const int index)
{
	return axis[index];
}
//allows float casting
Matrix2::operator float*()
{
	return (*data);
}

//adds two matricies
Matrix2 Matrix2::operator+(const Matrix2 & other) const
{
	return { xAxis + other.xAxis, yAxis + other.yAxis };
}
//adds a scalar to a matrix
Matrix2 Matrix2::operator+(const float scalar) const
{
	return { xAxis + scalar, yAxis + scalar };
}

//subtracts a matrix from a matrix
Matrix2 Matrix2::operator-(const Matrix2 & other) const
{
	return { xAxis - other.xAxis, yAxis - other.yAxis };
}
//subtracts a scalar from a matrix
Matrix2 Matrix2::operator-(const float scalar) const
{
	return { xAxis - scalar, yAxis - scalar };
}

//multiplies a matrix by a matrix
Matrix2 Matrix2::operator*(const Matrix2 & other) const
{
	//will contain the result of the multiplication
	Matrix2 result;

	//iterates for each row
	for (int row = 0; row < 2; row++)
	{
		//iterates for each column
		for (int col = 0; col < 2; col++)
		{
			//a dot product is performed between the rows of the first matrix against the columns of the second matrix
			result.data[col][row] = data[0][row] * other.data[col][0] +
									data[1][row] * other.data[col][1];
		}
	}

	return result;
}
//multiplies a matrix by a vector
Vector2 Matrix2::operator*(const Vector2 & other) const
{
	//will contain the result of the multiplication
	Vector2 result;

	//iterates for each row
	for (int row = 0; row < 2; row++)
	{
		//a dot product is performed between the rows of the first matrix against the columns of the second matrix
		//because the second matrix is a vector it only has one column
		result[row] = data[0][row] * other.data[0] +
					  data[1][row] * other.data[1];
	}

	return result;
}
//multiplies a matric by a scalar
Matrix2 Matrix2::operator*(const float scalar) const
{
	return { xAxis * scalar, yAxis * scalar };
}

//swaps the columns and rows
Matrix2 Matrix2::transposed() const
{
	//will contain the inverted columns and rows
	Matrix2 result;

	for (int row = 0; row < 2; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			//sets the coordinates to the opposite of the old coordinates
			result.data[row][col] = data[col][row];
		}
	}

	return result;
}

//assigns a matrix to the matrix
Matrix2 & Matrix2::operator=(const Matrix2 & other)
{
	xAxis = other.xAxis; yAxis = other.yAxis;
	return *this;
}
//assigns a scalar to the matrix
Matrix2 & Matrix2::operator=(const float scalar)
{
	xAxis = scalar; yAxis = scalar;
	return *this;
}

//increments the matrix by a matrix
Matrix2 & Matrix2::operator+=(const Matrix2 & other)
{
	*this = *this + other;
	return *this;
}
//increments the matrix by a scalar
Matrix2 & Matrix2::operator+=(const float scalar)
{
	*this = *this + scalar;
	return *this;
}

//pre-increments the matrix
Matrix2 & Matrix2::operator++()
{
	++xAxis; ++yAxis;
	return *this;
}
//post-increments the matrix
Matrix2 Matrix2::operator++(int)
{
	const Matrix2 old(*this);
	++(*this).xAxis; ++(*this).yAxis;
	return old;
}

//decrements the matrix by a matrix
Matrix2 & Matrix2::operator-=(const Matrix2 & other)
{
	*this = *this - other;
	return *this;
}
//decrements the matrix by a scalar
Matrix2 & Matrix2::operator-=(const float scalar)
{
	*this = *this - scalar;
	return *this;
}

//pre-decrements the matrix
Matrix2 & Matrix2::operator--()
{
	--xAxis; --yAxis;
	return *this;
}
//post-decrements the matrix
Matrix2 Matrix2::operator--(int)
{
	const Matrix2 old(*this);
	--(*this).xAxis; --(*this).yAxis;
	return old;
}

//multiplies the matrix by a matrix
Matrix2 & Matrix2::operator*=(const Matrix2 & other)
{
	*this = *this * other;
	return *this;
}
//multiplies the matrix by a scalar
Matrix2 & Matrix2::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

//checks if the matrix is equal to another matrix
bool Matrix2::operator==(const Matrix2 & other) const
{
	if (xAxis == other.xAxis && yAxis == other.yAxis)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is equal to a scalar
bool Matrix2::operator==(const float scalar) const
{
	if (xAxis == scalar && yAxis == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the matrix is not equal to another matrix
bool Matrix2::operator!=(const Matrix2 & other) const
{
	if (xAxis != other.xAxis || yAxis != other.yAxis)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is not equal to a scalar
bool Matrix2::operator!=(const float scalar) const
{
	if (xAxis != scalar || yAxis != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//creates a scaled matrix based on a different scale for each axis
void Matrix2::setScaled(const float x, const float y)
{
	//sets the values of the main diagonal of the matrix to the specified values
	xAxis = { x, 0.0f };
	yAxis = { 0.0f, y };
}
//creates a scaled matrix based on a vector
void Matrix2::setScaled(const Vector2 & vec)
{
	xAxis = { vec.x, 0.0f };
	yAxis = { 0.0f, vec.y };
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix2::scale(const float x, const float y)
{
	//scaled matrix
	Matrix2 mat;
	mat.setScaled(x, y);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix2::scale(const Vector2 & vec)
{
	//scaled matrix
	Matrix2 mat;
	mat.setScaled(vec.x, vec.y);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle
void Matrix2::setRotate(const float radians)
{
	//rotates the axis elements using sin and cos of the angle
	xAxis = { cosf(radians), sinf(radians) };
	yAxis = { -sinf(radians), cosf(radians) };
}
//creates a rotated matrix and multiplies this matrix with the rotated matrix
void Matrix2::rotate(const float radians)
{
	//rotated matrix
	Matrix2 mat;
	mat.setRotate(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}