#include "Matrix4.h"
#include <math.h>

//sets default values for the matrix
Matrix4::Matrix4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			//since the array is in union with the coordinates both the array and the coordinates will become 0
			data[i][j] = 0.0f;
		}
	}
}
//allows specific values to be set for the matrix elements
Matrix4::Matrix4(const float Xx, const float Xy, const float Xz, const float Xw, const float Yx, const float Yy, const float Yz, const float Yw, const float Zx, const float Zy, const float Zz, const float Zw, const float Tx, const float Ty, const float Tz, const float Tw)
{
	data[0][0] = Xx; data[1][0] = Yx; data[2][0] = Zx; data[3][0] = Tx;
	data[0][1] = Xy; data[1][1] = Yy; data[2][1] = Zy; data[3][1] = Ty;
	data[0][2] = Xz; data[1][2] = Yz; data[2][2] = Zz; data[3][2] = Tz;
	data[0][3] = Xw; data[1][3] = Yw; data[2][3] = Zw; data[3][3] = Tw;
}
//allows specific vectors to be set for the axis
Matrix4::Matrix4(const Vector4 X, const Vector4 Y, const Vector4 Z, const Vector4 T)
{
	xAxis = X;
	yAxis = Y;
	zAxis = Z;
	translation = T;
}
Matrix4::~Matrix4()
{
}

//contains the identity matrix for a matrix 4
const Matrix4 Matrix4::identity = Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

//allows for iteration of the array
Vector4 & Matrix4::operator[](const int index)
{
	return axis[index];
}
//allows float casting
Matrix4::operator float*()
{
	return (*data);
}

//adds two matricies
Matrix4 Matrix4::operator+(const Matrix4 & other) const
{
	return { xAxis + other.xAxis, yAxis + other.yAxis, zAxis + other.zAxis, translation + other.translation };
}
//adds a scalar to a matrix
Matrix4 Matrix4::operator+(const float scalar) const
{
	return { xAxis + scalar, yAxis + scalar, zAxis + scalar, translation + scalar };
}

//subtracts a matrix from a matrix
Matrix4 Matrix4::operator-(const Matrix4 & other) const
{
	return { xAxis - other.xAxis, yAxis - other.yAxis, zAxis - other.zAxis, translation - other.translation };
}
//subtracts a scalar from a matrix
Matrix4 Matrix4::operator-(const float scalar) const
{
	return { xAxis - scalar, yAxis - scalar, zAxis - scalar, translation - scalar };
}

//multiplies a matrix by a matrix
Matrix4 Matrix4::operator*(const Matrix4 & other) const
{
	//will contain the result of the multiplication
	Matrix4 result;

	//iterates for each row
	for (int row = 0; row < 4; row++)
	{
		//iterates for each column
		for (int col = 0; col < 4; col++)
		{
			//a dot product is performed between the rows of the first matrix against the columns of the second matrix
			result.data[col][row] = data[0][row] * other.data[col][0] +
									data[1][row] * other.data[col][1] +
									data[2][row] * other.data[col][2] +
									data[3][row] * other.data[col][3];
		}
	}

	return result;
}
//multiplies a matrix by a vector
Vector4 Matrix4::operator*(const Vector4 & other) const
{
	//will contain the result of the multiplication
	Vector4 result;

	//iterates for each row
	for (int row = 0; row < 4; row++)
	{
		//a dot product is performed between the rows of the first matrix against the columns of the second matrix
		//because the second matrix is a vector it only has one column
		result[row] = data[0][row] * other.data[0] +
					  data[1][row] * other.data[1] +
					  data[2][row] * other.data[2] +
					  data[3][row] * other.data[3];
	}

	return result;
}
//multiplies a matric by a scalar
Matrix4 Matrix4::operator*(const float scalar) const
{
	return { xAxis * scalar, yAxis * scalar, zAxis * scalar, translation * scalar };
}

//swaps the columns and rows
Matrix4 Matrix4::transposed() const
{
	//will contain the inverted columns and rows
	Matrix4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			//sets the coordinates to the opposite of the old coordinates
			result.data[row][col] = data[col][row];
		}
	}

	return result;
}

//assigns a matrix to the matrix
Matrix4 & Matrix4::operator=(const Matrix4 & other)
{
	xAxis = other.xAxis; yAxis = other.yAxis; zAxis = other.zAxis; translation = other.translation;
	return *this;
}
//assigns a scalar to the matrix
Matrix4 & Matrix4::operator=(const float scalar)
{
	xAxis = scalar; yAxis = scalar; zAxis = scalar; translation = scalar;
	return *this;
}

//increments the matrix by a matrix
Matrix4 & Matrix4::operator+=(const Matrix4 & other)
{
	*this = *this + other;
	return *this;
}
//increments the matrix by a scalar
Matrix4 & Matrix4::operator+=(const float scalar)
{
	*this = *this + scalar;
	return *this;
}

//pre-increments the matrix
Matrix4 & Matrix4::operator++()
{
	++xAxis; ++yAxis; ++zAxis; ++translation;
	return *this;
}
//post-increments the matrix
Matrix4 Matrix4::operator++(int)
{
	const Matrix4 old(*this);
	++(*this).xAxis; ++(*this).yAxis; ++(*this).zAxis; ++(*this).translation;
	return old;
}

//decrements the matrix by a matrix
Matrix4 & Matrix4::operator-=(const Matrix4 & other)
{
	*this = *this - other;
	return *this;
}
//decrements the matrix by a scalar
Matrix4 & Matrix4::operator-=(const float scalar)
{
	*this = *this - scalar;
	return *this;
}

//pre-decrements the matrix
Matrix4 & Matrix4::operator--()
{
	--xAxis; --yAxis; --zAxis; --translation;
	return *this;
}
//post-decrements the matrix
Matrix4 Matrix4::operator--(int)
{
	const Matrix4 old(*this);
	--(*this).xAxis; --(*this).yAxis; --(*this).zAxis; --(*this).translation;
	return old;
}

//multiplies the matrix by a matrix
Matrix4 & Matrix4::operator*=(const Matrix4 & other)
{
	*this = *this * other;
	return *this;
}
//multiplies the matrix by a scalar
Matrix4 & Matrix4::operator*=(const float scalar)
{
	*this = *this * scalar;
	return *this;
}

//checks if the matrix is equal to another matrix
bool Matrix4::operator==(const Matrix4 & other) const
{
	if (xAxis == other.xAxis && yAxis == other.yAxis && zAxis == other.zAxis && translation == other.translation)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is equal to a scalar
bool Matrix4::operator==(const float scalar) const
{
	if (xAxis == scalar && yAxis == scalar && zAxis == scalar && translation == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the matrix is not equal to another matrix
bool Matrix4::operator!=(const Matrix4 & other) const
{
	if (xAxis != other.xAxis || yAxis != other.yAxis || zAxis != other.zAxis || translation != other.translation)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the matrix is not equal to a scalar
bool Matrix4::operator!=(const float scalar) const
{
	if (xAxis != scalar || yAxis != scalar || zAxis != scalar || translation != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//creates a scaled matrix based on a different scale for each axis
void Matrix4::setScaled(const float x, const float y, const float z)
{
	//sets the values of the main diagonal of the matrix to the specified values
	xAxis = { x, 0.0f, 0.0f };
	yAxis = { 0.0f, y, 0.0f };
	zAxis = { 0.0f, 0.0f, z };
	translation = { 0.0f, 0.0f, 0.0f, 1.0f };
}
//creates a scaled matrix based on a vector
void Matrix4::setScaled(const Vector4 & vec)
{
	xAxis = { vec.x, 0.0f, 0.0f };
	yAxis = { 0.0f, vec.y, 0.0f };
	zAxis = { 0.0f, 0.0f, vec.z };
	translation = { 0.0f, 0.0f, 0.0f, 1.0f };
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix4::scale(const float x, const float y, const float z)
{
	//scaled matrix
	Matrix4 mat;
	mat.setScaled(x, y, z);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}
//creates a scaled matrix and multiplies this matrix with the scaled matrix
void Matrix4::scale(const Vector4 & vec)
{
	//scaled matrix
	Matrix4 mat;
	mat.setScaled(vec.x, vec.y, vec.z);
	//multiplies this matrix by the scaled matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the x axis
void Matrix4::setRotateX(const float radians)
{
	//rotates the matrix around the x axis by keeping the x axis still
	xAxis = { 1.0f, 0.0f, 0.0f };
	yAxis = { 0.0f, cosf(radians), sinf(radians) };
	zAxis = { 0.0f, -sinf(radians), cosf(radians) };
	translation = { 0.0f, 0.0f, 0.0f, 1.0f };
}
//creates a rotated x matrix and multiplies this matrix with the rotated matrix
void Matrix4::rotateX(const float radians)
{
	//rotated matrix
	Matrix4 mat;
	mat.setRotateX(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the y axis
void Matrix4::setRotateY(const float radians)
{
	//rotates the matrix around the y axis by keeping the y axis still
	xAxis = { cosf(radians), 0.0f, -sinf(radians) };
	yAxis = { 0.0f, 1.0f, 0.0f };
	zAxis = { sinf(radians), 0.0f, cosf(radians) };
	translation = { 0.0f, 0.0f, 0.0f, 1.0f };
}
//creates a rotated y matrix and multiplies this matrix with the rotated matrix
void Matrix4::rotateY(const float radians)
{
	//rotated matrix
	Matrix4 mat;
	mat.setRotateY(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on an angle around the z axis
void Matrix4::setRotateZ(const float radians)
{
	//rotates the matrix around the z axis by keeping the z axis still
	xAxis = { cosf(radians), sinf(radians), 0.0f };
	yAxis = { -sinf(radians), cosf(radians), 0.0f };
	zAxis = { 0.0f, 0.0f, 1.0f };
	translation = { 0.0f, 0.0f, 0.0f, 1.0f };
}
//creates a rotated z matrix and multiplies this matrix with the rotated matrix
void Matrix4::rotateZ(const float radians)
{
	//rotated matrix
	Matrix4 mat;
	mat.setRotateZ(radians);
	//multiplies this matrix by the rotated matrix
	*this = *this * mat;
}

//creates a rotated matrix based on euler angles
void Matrix4::setEuler(const float pitch, const float yaw, const float roll)
{
	//creates a rotated matrix for each axis
	Matrix4 x, y, z;
	x.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateZ(roll);
	//multiplies the scales in a specific order
	*this = z * y * x;
}

//translates an existing matrix
void Matrix4::translate(const float x, const float y, const float z)
{
	//increments the translation by the specified amount
	translation += Vector4(x, y, z, 0);
}