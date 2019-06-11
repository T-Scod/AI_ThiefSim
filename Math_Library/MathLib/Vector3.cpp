#include "Vector3.h"
#include <iostream>

//sets default values for the vector
Vector3::Vector3()
{
	for (int i = 0; i < 2; i++)
	{
		//since the array is in union with the coordinates both the array and the coordinates will become 0
		data[i] = 0.0f;
	}
}
//allows specific values to be set for the vector
Vector3::Vector3(const float x, const float y, const float z)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
}
Vector3::~Vector3()
{
}

//projects a vector onto another vector resulting in a scalar value
//if unit-length vectors are used then the dot product can be used to find the angle between the two vectors
float Vector3::dot(const Vector3 & other) const
{
	return x * other.x + y * other.y + z * other .z;
}
//creates a vector perpendicular to two existing vectors
Vector3 Vector3::cross(const Vector3 & other) const
{
	return { y * other.z - z * other.y,
			 z * other.x - x * other.z,
			 x * other.y - y * other.x };
}
//returns the angle between vectors
float Vector3::angleBetween(const Vector3 & other) const
{
	//sets this vector and the other vector to new variables so that normalising them doesn't change the originals
	Vector3 a = { x, y, z };
	a.normalise();
	Vector3 b = other;
	b.normalise();
	//calculates the angle between the vectors
	float angle = acosf(a.dot(b));

	//finds prependicular vector by finding the cross product
	Vector3 perp = b.cross({ 0, 0, 1 });
	//finds what side of the target vector this vector is on
	float perpDot = perp.dot(a);

	//changes rotation if on the other side of the target vector
	if (perpDot < 0.0f)
	{
		angle = (4.0f * asinf(1.0f)) - angle;
	}

	return angle;
}

//returns the perpendicular vector along the x axis
Vector3 Vector3::getPerpendicularRH() const
{
	return { y, -x };
}
//returns the perpendicular vector along the y axis
Vector3 Vector3::getPerpendicularLH() const
{
	return { -y, x };
}

//returns the length of the vector
float Vector3::magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}
//returns the square of the magnitude which allows for faster processing if the only necessity for the magnitude is to compare it to another
float Vector3::magnitudeSqr() const
{
	return (x * x + y * y + z * z);
}
//determines the distance between two vectors
float Vector3::distance(const Vector3 & other) const
{
	//distance is found by finding the difference between the points
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	//returns the magnitude of the vector
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}
//determines the square of the distance between two vectors which allows for faster processing if the only necessity for the distance is to compare it to another
float Vector3::distanceSqr(const Vector3 & other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	return (diffX * diffX + diffY * diffY + diffZ * diffZ);
}
//scales the vector to unit-length
void Vector3::normalise()
{
	//by dividing the opposite, adjacent and depth by the hypotenuse the vector becomes a unit of magnitude 1
	float mag = sqrt(x * x + y * y + z * z);
	x /= mag;
	y /= mag;
	z /= mag;
}

//allows for iteration of the array
float & Vector3::operator[](const int index)
{
	return data[index];
}
//allows float casting
Vector3::operator float*()
{
	return data;
}
//returns the inverse of the vector
Vector3 & Vector3::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	return *this;
}

//adds two vectors
Vector3 Vector3::operator+(const Vector3 & other) const
{
	return { x + other.x, y + other.y, z + other.z };
}
//adds a scalar to a vector
Vector3 Vector3::operator+(const float scalar) const
{
	return { x + scalar, y + scalar, z + scalar };
}

//subtracts a vector from a vector
Vector3 Vector3::operator-(const Vector3 & other) const
{
	return { x - other.x, y - other.y, z - other.z };
}
//subtracts a scalar from a vector
Vector3 Vector3::operator-(const float scalar) const
{
	return { x - scalar, y - scalar, z - scalar };
}

//multiplies two vectors
Vector3 Vector3::operator*(const Vector3 & other) const
{
	return { x * other.x, y * other.y, z * other.z };
}
//multiplies a vector by a scalar
Vector3 Vector3::operator*(const float scalar) const
{
	return { x * scalar, y * scalar, z * scalar };
}

//divides a vector by a vector
Vector3 Vector3::operator/(const Vector3 & other) const
{
	return { x / other.x, y / other.y, z / other.z };
}
//divides a vector by a scalar
Vector3 Vector3::operator/(const float scalar) const
{
	return { x / scalar, y / scalar, z / scalar };
}

//assigns a vector to the vector
Vector3 & Vector3::operator=(const Vector3 & other)
{
	x = other.x; y = other.y; z = other.z;
	return *this;
}
//assigns a scalar to the vector
Vector3 & Vector3::operator=(const float scalar)
{
	x = scalar; y = scalar; z = scalar;
	return *this;
}

//increments the vector by a vector
Vector3 & Vector3::operator+=(const Vector3 & other)
{
	x += other.x; y += other.y; z += other.z;
	return *this;
}
//increments the vector by a scalar
Vector3 & Vector3::operator+=(const float scalar)
{
	x += scalar; y += scalar; z += scalar;
	return *this;
}

//pre-increments the vector
Vector3& Vector3::operator++()
{
	++x; ++y; ++z;
	return *this;
}
//post-increments the vector
Vector3 Vector3::operator++(int)
{
	const Vector3 old(*this);
	++(*this).x; ++(*this).y; ++(*this).z;
	return old;
}

//decrements the vector by a vector
Vector3 & Vector3::operator-=(const Vector3 & other)
{
	x -= other.x; y -= other.y; z -= other.z;
	return *this;
}
//decrements the vector by a scalar
Vector3 & Vector3::operator-=(const float scalar)
{
	x -= scalar; y -= scalar; z -= scalar;
	return *this;
}

//pre-decrements the vector
Vector3 & Vector3::operator--()
{
	--x; --y; --z;
	return *this;
}
//post-decrements the vector
Vector3 Vector3::operator--(int)
{
	const Vector3 old(*this);
	--(*this).x; --(*this).y; --(*this).z;
	return old;
}

//multiplies the vector by a vector 
Vector3 & Vector3::operator*=(const Vector3 & other)
{
	x *= other.x; y *= other.y; z *= other.z;
	return *this;
}
//multiplies the vector by a scalar
Vector3 & Vector3::operator*=(const float scalar)
{
	x *= scalar; y *= scalar; z *= scalar;
	return *this;
}

//divides the vector by a vector
Vector3 & Vector3::operator/=(const Vector3 & other)
{
	x /= other.x; y /= other.y; z /= other.z;
	return *this;
}
//divides the vector by a scalar
Vector3 & Vector3::operator/=(const float scalar)
{
	x /= scalar; y /= scalar; z /= scalar;
	return *this;
}

//checks if the vector is equal to another vector
bool Vector3::operator==(const Vector3 & other) const
{
	if (x == other.x && y == other.y && z == other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is equal to a scalar
bool Vector3::operator==(const float scalar) const
{
	if (x == scalar && y == scalar && z == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is not equal to another vector
bool Vector3::operator!=(const Vector3 & other) const
{
	if (x != other.x || y != other.y || z != other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is not equal to a scalar
bool Vector3::operator!=(const float scalar) const
{
	if (x != scalar || y != scalar || z != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than or equal to another vector
bool Vector3::operator<=(const Vector3 & other) const
{
	if (x <= other.x && y <= other.y && z <= other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than or equal to a scalar
bool Vector3::operator<=(const float scalar) const
{
	if (x <= scalar && y <= scalar && z <= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than or equal to another vector
bool Vector3::operator>=(const Vector3 & other) const
{
	if (x >= other.x && y >= other.y && z >= other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than or equal to a scalar
bool Vector3::operator>=(const float scalar) const
{
	if (x >= scalar && y >= scalar && z >= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than another vector
bool Vector3::operator<(const Vector3 & other) const
{
	if (x < other.x && y < other.y && z < other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than a scalar
bool Vector3::operator<(const float scalar) const
{
	if (x < scalar && y < scalar && z < scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than another vector
bool Vector3::operator>(const Vector3 & other) const
{
	if (x > other.x && y > other.y && z > other.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than a scalar
bool Vector3::operator>(const float scalar) const
{
	if (x > scalar && y > scalar && z > scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//adds a vector to a scalar
Vector3 operator+(const float scalar, const Vector3 & other)
{
	return { other.x + scalar, other.y + scalar, other.z + scalar };
}
//subtracts a vector from a scalar
Vector3 operator-(const float scalar, const Vector3 & other)
{
	return { other.x - scalar, other.y - scalar, other.z - scalar };
}
//multiplies a scalar by a vector
Vector3 operator*(const float scalar, const Vector3 & other)
{
	return { other.x * scalar, other.y * scalar, other.z * scalar };
}
//divides a scalar by a vector
Vector3 operator/(const float scalar, const Vector3 & other)
{
	return { other.x / scalar, other.y / scalar, other.z / scalar };
}