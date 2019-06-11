#pragma once
#include "Vector2.h"

class Matrix2
{
public:
	//sets default values for the matrix
	Matrix2();
	//allows specific values to be set for the matrix elements
	Matrix2(const float Xx, const float Xy = 0.0f, const float Yx = 0.0f, const float Yy = 0.0f);
	//allows specific vectors to be set for the axis
	Matrix2(const Vector2 X, const Vector2 Y = 0.0f);
	~Matrix2();

	//allows the sharing of memory between the vectors and the arrays
	union
	{
		struct
		{
			//contains the X column
			Vector2 xAxis;
			//contains the Y column
			Vector2 yAxis;
		};
		//contains both columns
		Vector2 axis[2];
		//contains all elements in columns and rows
		float data[2][2];
	};

	//contains the identity matrix for a matrix 2
	static const Matrix2 identity;
	
	//allows for iteration of the array
	Vector2& operator [] (const int index);
	//allows float casting
	operator float* ();
	
	//adds two matricies
	Matrix2 operator + (const Matrix2& other) const;
	//adds a scalar to a matrix
	Matrix2 operator + (const float scalar) const;
	//subtracts a matrix from a matrix
	Matrix2 operator - (const Matrix2& other) const;
	//subtracts a scalar from a matrix
	Matrix2 operator - (const float scalar) const;
	//multiplies a matrix by a matrix
	Matrix2 operator * (const Matrix2& other) const;
	//multiplies a matrix by a vector
	Vector2 operator * (const Vector2& other) const;
	//multiplies a matric by a scalar
	Matrix2 operator * (const float scalar) const;

	//swaps the columns and rows
	Matrix2 transposed() const;

	//assigns a matrix to the matrix
	Matrix2& operator = (const Matrix2& other);
	//assigns a scalar to the matrix
	Matrix2& operator = (const float scalar);
	//increments the matrix by a matrix
	Matrix2& operator += (const Matrix2& other);
	//increments the matrix by a scalar
	Matrix2& operator += (const float scalar);
	//pre-increments the matrix
	Matrix2& operator ++ ();
	//post-increments the matrix
	Matrix2 operator ++ (int);
	//decrements the matrix by a matrix
	Matrix2& operator -= (const Matrix2& other);
	//decrements the matrix by a scalar
	Matrix2& operator -= (const float scalar);
	//pre-decrements the matrix
	Matrix2& operator -- ();
	//post-decrements the matrix
	Matrix2 operator -- (int);
	//multiplies the matrix by a matrix
	Matrix2& operator *= (const Matrix2& other);
	//multiplies the matrix by a scalar
	Matrix2& operator *= (const float scalar);

	//checks if the matrix is equal to another matrix
	bool operator == (const Matrix2& other) const;
	//checks if the matrix is equal to a scalar
	bool operator == (const float scalar) const;
	//checks if the matrix is not equal to another matrix
	bool operator != (const Matrix2& other) const;
	//checks if the matrix is not equal to a scalar
	bool operator != (const float scalar) const;

	//creates a scaled matrix based on a different scale for each axis
	void setScaled(const float x, const float y);
	//creates a scaled matrix based on a vector
	void setScaled(const Vector2& vec);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const float x, const float y);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const Vector2& vec);
	//creates a rotated matrix based on an angle
	void setRotate(const float radians);
	//creates a rotated matrix and multiplies this matrix with the rotated matrix
	void rotate(const float radians);
};