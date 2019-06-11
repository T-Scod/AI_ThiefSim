#pragma once

class Vector3
{
public:
	//sets default values for the vector
	Vector3();
	//allows specific values to be set for the vector
	Vector3(const float x, const float y = 0.0f, const float z = 0.0f);
	~Vector3();

	//allows the sharing of memory between the floats and the array
	union
	{
		struct
		{
			float x, y;
			//allows the third element to be labelled as w or z
			union
			{
				float z, w;
			};
		};
		//contains the coordinates in an array such that data[0] == x, data[1] == y, data[2] == z and data[2] == w
		float data[3];
	};

	//projects a vector onto another vector resulting in a scalar value
	//if unit-length vectors are used then the dot product can be used to find the angle between the two vectors
	float dot(const Vector3& other) const;
	//creates a vector perpendicular to two existing vectors
	Vector3 cross(const Vector3& other) const;
	//returns the angle between vectors
	float angleBetween(const Vector3& other) const;
	//returns the perpendicular vector along the x axis
	Vector3 getPerpendicularRH() const;
	//returns the perpendicular vector along the y axis
	Vector3 getPerpendicularLH() const;

	//returns the length of the vector
	float magnitude() const;
	//returns the square of the magnitude which allows for faster processing if the only necessity for the magnitude is to compare it to another
	float magnitudeSqr() const;
	//determines the distance between two vectors
	float distance(const Vector3& other) const;
	//determines the square of the distance between two vectors which allows for faster processing if the only necessity for the distance is to compare it to another
	float distanceSqr(const Vector3& other) const;
	//scales the vector to unit-length
	void normalise();

	//allows for iteration of the array
	float& operator [] (const int index);
	//allows float casting
	operator float* ();
	//returns the inverse of the vector
	Vector3& operator - ();

	/*maths operators*/

	//adds two vectors
	Vector3 operator + (const Vector3& other) const;
	//adds a scalar to a vector
	Vector3 operator + (const float scalar) const;
	//adds a vector to a scalar
	friend Vector3 operator + (const float scalar, const Vector3& other);
	//subtracts a vector from a vector
	Vector3 operator - (const Vector3& other) const;
	//subtracts a scalar from a vector
	Vector3 operator - (const float scalar) const;
	//subtracts a vector from a scalar
	friend Vector3 operator - (const float scalar, const Vector3& other);
	//multiplies two vectors
	Vector3 operator * (const Vector3& other) const;
	//multiplies a vector by a scalar
	Vector3 operator * (const float scalar) const;
	//multiplies a scalar by a vector
	friend Vector3 operator * (const float scalar, const Vector3& other);
	//divides a vector by a vector
	Vector3 operator / (const Vector3& other) const;
	//divides a vector by a scalar
	Vector3 operator / (const float scalar) const;
	//divides a scalar by a vector
	friend Vector3 operator / (const float scalar, const Vector3& other);

	//assigns a vector to the vector
	Vector3& operator = (const Vector3& other);
	//assigns a scalar to the vector
	Vector3& operator = (const float scalar);
	//increments the vector by a vector
	Vector3& operator += (const Vector3& other);
	//increments the vector by a scalar
	Vector3& operator += (const float scalar);
	//pre-increments the vector
	Vector3& operator ++ ();
	//post-increments the vector
	Vector3 operator ++ (int);
	//decrements the vector by a vector
	Vector3& operator -= (const Vector3& other);
	//decrements the vector by a scalar
	Vector3& operator -= (const float scalar);
	//pre-decrements the vector
	Vector3& operator -- ();
	//post-decrements the vector
	Vector3 operator -- (int);
	//multiplies the vector by a vector 
	Vector3& operator *= (const Vector3& other);
	//multiplies the vector by a scalar
	Vector3& operator *= (const float scalar);
	//divides the vector by a vector
	Vector3& operator /= (const Vector3& other);
	//divides the vector by a scalar
	Vector3& operator /= (const float scalar);


	//checks if the vector is equal to another vector
	bool operator == (const Vector3& other) const;
	//checks if the vector is equal to a scalar
	bool operator == (const float scalar) const;
	//checks if the vector is not equal to another vector
	bool operator != (const Vector3& other) const;
	//checks if the vector is not equal to a scalar
	bool operator != (const float scalar) const;
	//checks if the vector is less than or equal to another vector
	bool operator <= (const Vector3& other) const;
	//checks if the vector is less than or equal to a scalar
	bool operator <= (const float scalar) const;
	//checks if the vector is greater than or equal to another vector
	bool operator >= (const Vector3& other) const;
	//checks if the vector is greater than or equal to a scalar
	bool operator >= (const float scalar) const;
	//checks if the vector is less than another vector
	bool operator < (const Vector3& other) const;
	//checks if the vector is less than a scalar
	bool operator < (const float scalar) const;
	//checks if the vector is greater than another vector
	bool operator > (const Vector3& other) const;
	//checks if the vector is greater than a scalar
	bool operator > (const float scalar) const;
};