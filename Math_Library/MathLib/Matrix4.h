#pragma once
#include "Vector4.h"

class Matrix4
{
public:
	//sets default values for the matrix
	Matrix4();
	//allows specific values to be set for the matrix elements
	Matrix4(const float Xx, const float Xy = 0.0f, const float Xz = 0.0f, const float Xw = 0.0f, const float Yx = 0.0f, const float Yy = 0.0f, const float Yz = 0.0f, const float Yw = 0.0f, const float Zx = 0.0f, const float Zy = 0.0f, const float Zz = 0.0f, const float Zw = 0.0f, const float Tx = 0.0f, const float Ty = 0.0f, const float Tz = 0.0f, const float Tw = 1.0f);
	//allows specific vectors to be set for the axis
	Matrix4(const Vector4 X, const Vector4 Y = 0.0f, const Vector4 Z = 0.0f, const Vector4 T = {0.0f, 0.0f, 0.0f, 1.0f});
	~Matrix4();

	//allows the sharing of memory between the vectors and the arrays
	union
	{
		struct
		{
			//contains the X column
			Vector4 xAxis;
			//contains the Y column
			Vector4 yAxis;
			//contains the Z column
			Vector4 zAxis;
			//contains the T column
			Vector4 translation;
		};
		//contains all four columns
		Vector4 axis[4];
		//contains all elements in columns and rows
		float data[4][4];
	};

	//contains the identity matrix for a matrix 4
	static const Matrix4 identity;

	//allows for iteration of the array
	Vector4& operator [] (const int index);
	//allows float casting
	operator float* ();

	//adds two matricies
	Matrix4 operator + (const Matrix4& other) const;
	//adds a scalar to a matrix
	Matrix4 operator + (const float scalar) const;
	//subtracts a matrix from a matrix
	Matrix4 operator - (const Matrix4& other) const;
	//subtracts a scalar from a matrix
	Matrix4 operator - (const float scalar) const;
	//multiplies a matrix by a matrix
	Matrix4 operator * (const Matrix4& other) const;
	//multiplies a matrix by a vector
	Vector4 operator * (const Vector4& other) const;
	//multiplies a matric by a scalar
	Matrix4 operator * (const float scalar) const;

	//swaps the columns and rows
	Matrix4 transposed() const;

	//assigns a matrix to the matrix
	Matrix4& operator = (const Matrix4& other);
	//assigns a scalar to the matrix
	Matrix4& operator = (const float scalar);
	//increments the matrix by a matrix
	Matrix4& operator += (const Matrix4& other);
	//increments the matrix by a scalar
	Matrix4& operator += (const float scalar);
	//pre-increments the matrix
	Matrix4& operator ++ ();
	//post-increments the matrix
	Matrix4 operator ++ (int);
	//decrements the matrix by a matrix
	Matrix4& operator -= (const Matrix4& other);
	//decrements the matrix by a scalar
	Matrix4& operator -= (const float scalar);
	//pre-decrements the matrix
	Matrix4& operator -- ();
	//post-decrements the matrix
	Matrix4 operator -- (int);
	//multiplies the matrix by a matrix
	Matrix4& operator *= (const Matrix4& other);
	//multiplies the matrix by a scalar
	Matrix4& operator *= (const float scalar);

	//checks if the matrix is equal to another matrix
	bool operator == (const Matrix4& other) const;
	//checks if the matrix is equal to a scalar
	bool operator == (const float scalar) const;
	//checks if the matrix is not equal to another matrix
	bool operator != (const Matrix4& other) const;
	//checks if the matrix is not equal to a scalar
	bool operator != (const float scalar) const;

	//creates a scaled matrix based on a different scale for each axis
	void setScaled(const float x, const float y, const float z);
	//creates a scaled matrix based on a vector
	void setScaled(const Vector4& vec);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const float x, const float y, const float z);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const Vector4& vec);
	//creates a rotated matrix based on an angle around the x axis
	void setRotateX(const float radians);
	//creates a rotated x matrix and multiplies this matrix with the rotated matrix
	void rotateX(const float radians);
	//creates a rotated matrix based on an angle around the y axis
	void setRotateY(const float radians);
	//creates a rotated y matrix and multiplies this matrix with the rotated matrix
	void rotateY(const float radians);
	//creates a rotated matrix based on an angle around the z axis
	void setRotateZ(const float radians);
	//creates a rotated z matrix and multiplies this matrix with the rotated matrix
	void rotateZ(const float radians);
	//creates a rotated matrix based on euler angles
	void setEuler(const float pitch, const float yaw, const float roll);

	//translates an existing matrix
	void translate(const float x, const float y, const float z);
};