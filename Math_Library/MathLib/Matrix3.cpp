#include "Matrix3.h"
#include <math.h>

//sets default values for the matrix
Matrix3::Matrix3()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			//since the array is in union with the coordinates both the array and the coordinates will become 0
			data[i][j] = 0.0f;
		}
	}
}
//allows specific values to be set for the matrix elements
Matrix3::Matrix3(const float Xx, const float Xy, const float Xz, const float Yx, const float Yy, const float Yz, const float Zx, const float Zy, const float Zz)
{
	data[0][0] = Xx; data[1][0] = Yx; data[2][0] = Zx;
	data[0][1] = Xy; data[1][1] = Yy; data[2][1] = Zy;
	data[0][2] = Xz; data[1][2] = Yz; data[2][2] = Zz;
}
//allows specific vectors to be set for the axis
Matrix3::Matrix3(const Vector3 X, const Vector3 Y, const Vector3 Z)
{
	xAxis = X;
	yAxis = Y;
	zAxis = Z;
}
Matrix3::~Matrix3()
{
}

//contains the identity matrix for a matrix 3
const Matrix3 Matrix3::identity = Matrix3(1, 0, 0, 0, 1, 0, 0, 0, 1);

//allows for iteration of the array
Vector3 & Matrix3::operator[](const int index)
{
	return axis[index];
}
//allows float casting
Matrix3::operator float*()
{
	return (*data);
}

//adds two matricies
Matrix3 Matrix3::operator+(const Matrix3 & other) const
{
	return { xAxis + other.xAxis, yAxis + other.yAxis, zAxis + other.zAxis };
}
//adds a scalar to a matrix
Matrix3 Matrix3::operator+(const float scalar) const
{
	return { xAxis + scalar, yAxis + scalar, zAxis + scalar };
}

//subtracts a matrix from a matrix
Matrix3 Matrix3::operator-(const Matrix3 & other) const
{
	return { xAxis - other.xAxis, yAxis - other.yAxis, zAxis - other.zAxis };
}
//subtracts a scalar from a matrix
Matrix3 Matrix3::operator-(const float scalar) const
{
	return { xAxis - scalar, yAxis - scalar, zAxis - scalar };
}

//multiplies a matrix by a matrix
Matrix3 Matrix3::operator*(const Matrix3 & other) const
{
	//will contain the result of the multiplication
	Matrix3 result;

	//iterates for each row
	for (int row = 0; row < 3; row++)
	{
		//iterates for each column
		for (int col = 0; col < 3; col++)
		{
			//a dot product is performed between the rows of the first matrix against the columns of the second matrix
			result.data[col][row] = data[0][row] * other.data[col][0] +
									data[1][row] * other.data[col][1] +
									data[2][row] * other.data[col][2];
		}
	}

	return result;
}
//multiplies a matrix by a vector
Vector3 Matrix3::operator*(const Vector3 & other) const
{
	//will contain the result of the multiplication
	Vector3 result;

	//iterates for each row
	for (int row = 0; row < 3; row++)
	{
		//a dot product is performed between the rows of the first matrix against the columns of the second matrix
		//because the second matrix is a vector it only has one column
		result[row] = data[0][row] * other.data[0] +
					  data[1][row] * other.data[1] +
					  data[2][row] * other.data[2];
	}

	return result;
}
//multiplies a matric by a scalar
Matrix3 Matrix3::operator*(const float scalar) const
{
	return { xAxis * scalar, yAxis * scalar, zAxis * scalar };
}

//swaps the columns and rows
Matrix3 Matrix3::transposed() const
{
	//will contain the inverted columns and rows
	Matrix3 result;

	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			//sets the coordinates to the opposite of the old coordinates
			result.data[row][col] = data[col][row];
		}
	}

	return result;
}

//assigns a matrix to the matrix
Matrix3 & Matrix3::operator=(const Matrix3 & other)
{
	xAxis = other.xAxis; yAxis = other.yAxis; zAxis = other.zAxis;
	return *this;
}
//assigns a scalar to the matrix
Matrix3 & Matrix3::operator=(const float scalar)
{
	xAxis = scalar; yAxis = scalar; zAxis = scalar;
	return *this;
}

//increments the matrix by a matrix
Matrix3 & Matrix3::operator+=(const Matrix3 & other)
{
	*this = *this + other;
	return *this;
}
//increments the matrix by a scalar
Matrix3 & Matrix3::operator+=(const float scalar)
{
	*this = *this + scalar;
	return *this;
}

//pre-increments the matrix
Matrix3 & Matrix3::operator++()
{
	++xAxis; ++yAxis; ++zAxis;
	return *this;
}
//post-increments the matrix
Matrix3 Matrix3::operator++(int)
{
	const Matrix3 old(*this);
	++(*this).xAxis; ++(*this).yAxis; ++(*this).zAxis;
	return old;
}

//decrements the matrix by a matrix
Matrix3 & Matrix3::operator-=(const Matrix3 & other)
{
	*this = *this - other;
	return *this;
}
//decrements the matrix by a scalar
Matrix3 & Matrix3::operator-=(const float scalar)
{
	*this = *this - scalar;
	return *this;
}

//pre-decrements the matrix
Matrix3 & Matrix3::operator--()
{
	--xAxis; --yAxis; --zAxis;
	return *this;
}
//post-decrements the matrix
Matrix3 Matrix3::operator--(int)
{
	const Matrix3 old(*this);
	--(*this).xAxis; --(*this).yAxis; --(*this).zAxis;
	return old;
}

//multiplies the matrix by a matrix
Matrix3 & Matrix3::operator*=(const Matrix3 & other)
{
	*this = *this * other;
	return *this;
}
//multiplies the matrix by a scalar
Matrix3 & Matrix3::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

//checks if the matrix is equal to another matrix
bool Matrix3::operator==(const Matrix3 & other) const
{
	if (xAxis == other.xAxis && yAxis == other.yAxis && zAxis == other.zAxis)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is equal to a scalar
bool Matrix3::operator==(const float scalar) const
{
	if (xAxis == scalar && yAxis == scalar && zAxis == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the matrix is not equal to another matrix
bool Matrix3::operator!=(const Matrix3 & other) const
{
	if (xAxis != other.xAxis || yAxis != other.yAxis || zAxis != other.zAxis)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is not equal to a scalar
bool Matrix3::operator!=(const float scalar) const
{
	if (xAxis != scalar || yAxis != scalar || zAxis != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//creates a scaled matrix based on a different scale for each axis
void Matrix3::setScaled(const float x, const float y, const float z)
{
	//sets the values of the main diagonal of the matrix to the specified values
	xAxis = { x, 0.0f, 0.0f };
	yAxis = { 0.0f, y, 0.0f };
	zAxis = { 0.0f, 0.0f, z };
}
//creates a scaled matrix based on a vector
void Matrix3::setScaled(const Vector3 & vec)
{
	xAxis = { vec.x, 0.0f, 0.0f };
	yAxis = { 0.0f, vec.y, 0.0f };
	zAxis = { 0.0f, 0.0f, vec.z };
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix3::scale(const float x, const float y, const float z)
{
	//scaled matrix
	Matrix3 mat;
	mat.setScaled(x, y, z);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix3::scale(const Vector3 & vec)
{
	//scaled matrix
	Matrix3 mat;
	mat.setScaled(vec.x, vec.y, vec.z);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the x axis
void Matrix3::setRotateX(const float radians)
{
	//rotates the matrix around the x axis by keeping the x axis still
	xAxis = { 1.0f, 0.0f, 0.0f };
	yAxis = { 0.0f, cosf(radians), sinf(radians) };
	zAxis = { 0.0f, -sinf(radians), cosf(radians) };
}
//creates a rotated x matrix and multiplies this matrix with the rotated matrix
void Matrix3::rotateX(const float radians)
{
	//rotated matrix
	Matrix3 mat;
	mat.setRotateX(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the y axis
void Matrix3::setRotateY(const float radians)
{
	//rotates the matrix around the y axis by keeping the y axis still
	xAxis = { cosf(radians), 0.0f, -sinf(radians) };
	yAxis = { 0.0f, 1.0f, 0.0f };
	zAxis = { sinf(radians), 0.0f, cosf(radians) };
}
//creates a rotated y matrix and multiplies this matrix with the rotated matrix
void Matrix3::rotateY(const float radians)
{
	//rotated matrix
	Matrix3 mat;
	mat.setRotateY(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the z axis
void Matrix3::setRotateZ(const float radians)
{
	//rotates the matrix around the z axis by keeping the z axis still
	xAxis = { cosf(radians), sinf(radians), 0.0f };
	yAxis = { -sinf(radians), cosf(radians), 0.0f };
	zAxis = { 0.0f, 0.0f, 1.0f };
}
//creates a rotated z matrix and multiplies this matrix with the rotated matrix
void Matrix3::rotateZ(const float radians)
{
	//rotated matrix
	Matrix3 mat;
	mat.setRotateZ(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on euler angles
void Matrix3::setEuler(const float pitch, const float yaw, const float roll)
{
	//creates a rotated matrix for each axis
	Matrix3 x, y, z;
	x.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateZ(roll);
	//multiplies the scales in a specific order
	*this = z * y * x;
}

//translates an existing matrix
void Matrix3::translate(const float x, const float y)
{
	//increments the translation by the specified amount
	translation += Vector3(x, y, 0);
}