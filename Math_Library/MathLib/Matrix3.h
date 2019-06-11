#pragma once
#include "Vector3.h"

class Matrix3
{
public:
	//sets default values for the matrix
	Matrix3();
	//allows specific values to be set for the matrix elements
	Matrix3(const float Xx, const float Xy = 0.0f, const float Xz = 0.0f, const float Yx = 0.0f, const float Yy = 0.0f, const float Yz = 0.0f, const float Zx = 0.0f, const float Zy = 0.0f, const float Zz = 0.0f);
	//allows specific vectors to be set for the axis
	Matrix3(const Vector3 X, const Vector3 Y = 0.0f, const Vector3 Z = 0.0f);
	~Matrix3();

	//allows the sharing of memory between the vectors and the arrays
	union
	{
		struct
		{
			//contains the X column
			Vector3 xAxis;
			//contains the Y column
			Vector3 yAxis;
			//allows the third axis to be labelled as Z or T
			union
			{
				Vector3 zAxis;
				Vector3 translation;
			};
		};
		//contains all three columns
		Vector3 axis[3];
		//contains all elements in columns and rows
		float data[3][3];
	};

	//contains the identity matrix for a matrix 3
	static const Matrix3 identity;

	//allows for iteration of the array
	Vector3& operator [] (const int index);
	//allows float casting
	operator float* ();

	//adds two matricies
	Matrix3 operator + (const Matrix3& other) const;
	//adds a scalar to a matrix
	Matrix3 operator + (const float scalar) const;
	//subtracts a matrix from a matrix
	Matrix3 operator - (const Matrix3& other) const;
	//subtracts a scalar from a matrix
	Matrix3 operator - (const float scalar) const;
	//multiplies a matrix by a matrix
	Matrix3 operator * (const Matrix3& other) const;
	//multiplies a matrix by a vector
	Vector3 operator * (const Vector3& other) const;
	//multiplies a matric by a scalar
	Matrix3 operator * (const float scalar) const;

	//swaps the columns and rows
	Matrix3 transposed() const;

	//assigns a matrix to the matrix
	Matrix3& operator = (const Matrix3& other);
	//assigns a scalar to the matrix
	Matrix3& operator = (const float scalar);
	//increments the matrix by a matrix
	Matrix3& operator += (const Matrix3& other);
	//increments the matrix by a scalar
	Matrix3& operator += (const float scalar);
	//pre-increments the matrix
	Matrix3& operator ++ ();
	//post-increments the matrix
	Matrix3 operator ++ (int);
	//decrements the matrix by a matrix
	Matrix3& operator -= (const Matrix3& other);
	//decrements the matrix by a scalar
	Matrix3& operator -= (const float scalar);
	//pre-decrements the matrix
	Matrix3& operator -- ();
	//post-decrements the matrix
	Matrix3 operator -- (int);
	//multiplies the matrix by a matrix
	Matrix3& operator *= (const Matrix3& other);
	//multiplies the matrix by a scalar
	Matrix3& operator *= (const float scalar);

	//checks if the matrix is equal to another matrix
	bool operator == (const Matrix3& other) const;
	//checks if the matrix is equal to a scalar
	bool operator == (const float scalar) const;
	//checks if the matrix is not equal to another matrix
	bool operator != (const Matrix3& other) const;
	//checks if the matrix is not equal to a scalar
	bool operator != (const float scalar) const;

	//creates a scaled matrix based on a different scale for each axis
	void setScaled(const float x, const float y, const float z);
	//creates a scaled matrix based on a vector
	void setScaled(const Vector3& vec);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const float x, const float y, const float z);
	//creates a scaled matrix and multiplies this matrix with the scaled matrix
	void scale(const Vector3& vec);
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
	void translate(const float x, const float y);
};