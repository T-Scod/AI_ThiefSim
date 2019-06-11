#include "Vector4.h"
#include <iostream>

//sets default values for the vector
Vector4::Vector4()
{
	for (int i = 0; i < 3; i++)
	{
		//since the array is in union with the coordinates both the array and the coordinates will become 0
		data[i] = 0.0f;
	}
}
//allows specific values to be set for the vector
Vector4::Vector4(const float x, const float y, const float z, const float w)
{
	data[0] = x;
	data[1] = y;
	data[2] = z;
	data[3] = w;
}
Vector4::~Vector4()
{
}

//projects a vector onto another vector resulting in a scalar value
//if unit-length vectors are used then the dot product can be used to find the angle between the two vectors
float Vector4::dot(const Vector4 & other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}
//creates a vector perpendicular to two existing vectors
Vector4 Vector4::cross(const Vector4 & other) const
{
	return { y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x, 0 };
}
//returns the angle between vectors
float Vector4::angleBetween(const Vector4 & other) const
{
	//sets this vector and the other vector to new variables so that normalising them doesn't change the originals
	Vector4 a = { x, y, z };
	a.normalise();
	Vector4 b = other;
	b.normalise();
	//calculates the angle between the vectors
	float angle = acosf(a.dot(b));

	//finds prependicular vector by finding the cross product
	Vector4 perp = b.cross({ 0, 0, 1 });
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
Vector4 Vector4::getPerpendicularRH() const
{
	return { y, -x };
}
//returns the perpendicular vector along the y axis
Vector4 Vector4::getPerpendicularLH() const
{
	return { -y, x };
}

//returns the length of the vector
float Vector4::magnitude() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
//returns the square of the magnitude which allows for faster processing if the only necessity for the magnitude is to compare it to another
float Vector4::magnitudeSqr() const
{
	return (x * x + y * y + z * z + w * w);
}
//determines the distance between two vectors
float Vector4::distance(const Vector4 & other) const
{
	//distance is found by finding the difference between the points
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	float diffW = w - other.w;
	//returns the magnitude of the vector
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}
//determines the square of the distance between two vectors which allows for faster processing if the only necessity for the distance is to compare it to another
float Vector4::distanceSqr(const Vector4 & other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	float diffW = w - other.w;
	return (diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}
//scales the vector to unit-length
void Vector4::normalise()
{
	//by dividing the opposite, adjacent, depth and homogenous transform by the hypotenuse the vector becomes a unit of magnitude 1
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	w /= mag;
}

//allows for iteration of the array
float & Vector4::operator[](const int index)
{
	return data[index];
}
//allows float casting
Vector4::operator float*()
{
	return data;
}
//returns the inverse of the vector
Vector4 & Vector4::operator-()
{
	x = -x;
	y = -y;
	z = -z;
	w = -w;
	return *this;
}

//adds two vectors
Vector4 Vector4::operator+(const Vector4 & other) const
{
	return { x + other.x, y + other.y, z + other.z, w + other.w };
}
//adds a scalar to a vector
Vector4 Vector4::operator+(const float scalar) const
{
	return { x + scalar, y + scalar, z + scalar, w + scalar };
}

//subtracts a vector from a vector
Vector4 Vector4::operator-(const Vector4 & other) const
{
	return { x - other.x, y - other.y, z - other.z, w - other.w };
}
//subtracts a scalar from a vector
Vector4 Vector4::operator-(const float scalar) const
{
	return { x - scalar, y - scalar, z - scalar, w - scalar };
}

//multiplies two vectors
Vector4 Vector4::operator*(const Vector4 & other) const
{
	return { x * other.x, y * other.y, z * other.z, w * other.w };
}
//multiplies a vector by a scalar
Vector4 Vector4::operator*(const float scalar) const
{
	return { x * scalar, y * scalar, z * scalar, w * scalar };
}

//divides a vector by a vector
Vector4 Vector4::operator/(const Vector4 & other) const
{
	return { x / other.x, y / other.y, z / other.z, w / other.w };
}
//divides a vector by a scalar
Vector4 Vector4::operator/(const float scalar) const
{
	return { x / scalar, y / scalar, z / scalar, w / scalar };
}

//assigns a vector to the vector
Vector4 & Vector4::operator=(const Vector4 & other)
{
	x = other.x; y = other.y; z = other.z; w = other.w;
	return *this;
}
//assigns a scalar to the vector
Vector4 & Vector4::operator=(const float scalar)
{
	x = scalar; y = scalar; z = scalar; w = scalar;
	return *this;
}

//increments the vector by a vector
Vector4 & Vector4::operator+=(const Vector4 & other)
{
	x += other.x; y += other.y; z += other.z; w += other.w;
	return *this;
}
//increments the vector by a scalar
Vector4 & Vector4::operator+=(const float scalar)
{
	x += scalar; y += scalar; z += scalar; w += scalar;
	return *this;
}

//pre-increments the vector
Vector4& Vector4::operator++()
{
	++x; ++y; ++z; ++w;
	return *this;
}
//post-increments the vector
Vector4 Vector4::operator++(int)
{
	const Vector4 old(*this);
	++(*this).x; ++(*this).y; ++(*this).z; ++(*this).w;
	return old;
}

//decrements the vector by a vector
Vector4 & Vector4::operator-=(const Vector4 & other)
{
	x -= other.x; y -= other.y; z -= other.z; w -= other.w;
	return *this;
}
//decrements the vector by a scalar
Vector4 & Vector4::operator-=(const float scalar)
{
	x -= scalar; y -= scalar; z -= scalar; w -= scalar;
	return *this;
}

//pre-decrements the vector
Vector4 & Vector4::operator--()
{
	--x; --y; --z; --w;
	return *this;
}
//post-decrements the vector
Vector4 Vector4::operator--(int)
{
	const Vector4 old(*this);
	--(*this).x; --(*this).y; --(*this).z; --(*this).w;
	return old;
}

//multiplies the vector by a vector 
Vector4 & Vector4::operator*=(const Vector4 & other)
{
	x *= other.x; y *= other.y; z *= other.z; w *= other.w;
	return *this;
}
//multiplies the vector by a scalar
Vector4 & Vector4::operator*=(const float scalar)
{
	x *= scalar; y *= scalar; z *= scalar; w *= scalar;
	return *this;
}

//divides the vector by a vector
Vector4 & Vector4::operator/=(const Vector4 & other)
{
	x /= other.x; y /= other.y; z /= other.z; w /= other.w;
	return *this;
}
//divides the vector by a scalar
Vector4 & Vector4::operator/=(const float scalar)
{
	x /= scalar; y /= scalar; z /= scalar; w /= scalar;
	return *this;
}

//checks if the vector is equal to another vector
bool Vector4::operator==(const Vector4 & other) const
{
	if (x == other.x && y == other.y && z == other.z && w == other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is equal to a scalar
bool Vector4::operator==(const float scalar) const
{
	if (x == scalar && y == scalar && z == scalar && w == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is not equal to another vector
bool Vector4::operator!=(const Vector4 & other) const
{
	if (x != other.x || y != other.y || z != other.z || w != other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is not equal to a scalar
bool Vector4::operator!=(const float scalar) const
{
	if (x != scalar || y != scalar || z != scalar || w != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than or equal to another vector
bool Vector4::operator<=(const Vector4 & other) const
{
	if (x <= other.x && y <= other.y && z <= other.z && w <= other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than or equal to a scalar
bool Vector4::operator<=(const float scalar) const
{
	if (x <= scalar && y <= scalar && z <= scalar && w <= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than or equal to another vector
bool Vector4::operator>=(const Vector4 & other) const
{
	if (x >= other.x && y >= other.y && z >= other.z && w >= other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than or equal to a scalar
bool Vector4::operator>=(const float scalar) const
{
	if (x >= scalar && y >= scalar && z >= scalar && w >= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than another vector
bool Vector4::operator<(const Vector4 & other) const
{
	if (x < other.x && y < other.y && z < other.z && w < other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than a scalar
bool Vector4::operator<(const float scalar) const
{
	if (x < scalar && y < scalar && z < scalar && w < scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than another vector
bool Vector4::operator>(const Vector4 & other) const
{
	if (x > other.x && y > other.y && z > other.z && w > other.w)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than a scalar
bool Vector4::operator>(const float scalar) const
{
	if (x > scalar && y > scalar && z > scalar && w > scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//adds a vector to a scalar
Vector4 operator+(const float scalar, const Vector4 & other)
{
	return { other.x + scalar, other.y + scalar, other.z + scalar, other.w + scalar };
}
//subtracts a vector from a scalar
Vector4 operator-(const float scalar, const Vector4 & other)
{
	return { other.x - scalar, other.y - scalar, other.z - scalar, other.w - scalar };
}
//multiplies a scalar by a vector
Vector4 operator*(const float scalar, const Vector4 & other)
{
	return { other.x * scalar, other.y * scalar, other.z * scalar, other.w * scalar };
}
//divides a scalar by a vector
Vector4 operator/(const float scalar, const Vector4 & other)
{
	return { other.x / scalar, other.y / scalar, other.z / scalar, other.w / scalar };
}