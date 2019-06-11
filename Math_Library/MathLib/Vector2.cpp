#include "Vector2.h"
#include <iostream>

//sets default values for the vector
Vector2::Vector2()
{
	for (int i = 0; i < 2; i++)
	{
		//since the array is in union with the coordinates both the array and the coordinates will become 0
		data[i] = 0.0f;
	}
}
//allows specific values to be set for the vector
Vector2::Vector2(const float x, const float y)
{
	data[0] = x;
	data[1] = y;
}
Vector2::~Vector2()
{
}

//projects a vector onto another vector resulting in a scalar value
//if unit-length vectors are used then the dot product can be used to find the angle between the two vectors
float Vector2::dot(const Vector2 & other) const
{
	return x * other.x + y * other.y;
}
//returns the perpendicular vector along the x axis
Vector2 Vector2::getPerpendicularRH() const
{
	return { y, -x };
}
//returns the perpendicular vector along the y axis
Vector2 Vector2::getPerpendicularLH() const
{
	return { -y, x };
}
//returns the angle between vectors
float Vector2::angleBetween(const Vector2 & other) const
{
	//sets this vector and the other vector to new variables so that normalising them doesn't change the originals
	Vector2 a = { x, y };
	a.normalise();
	Vector2 b = other;
	b.normalise();

	//calculate the dot product
	float d = a.dot(b);
	//returns the angle between the vectors
	return acos(d);
}
//the cross product between two Vector3's where z = 0
float Vector2::cross(const Vector2 & other) const
{
	return (x * other.y - other.x * y);
}

//returns the length of the vector
float Vector2::magnitude() const
{
	return sqrt(x * x + y * y);
}
//returns the square of the magnitude which allows for faster processing if the only necessity for the magnitude is to compare it to another
float Vector2::magnitudeSqr() const
{
	return (x * x + y * y);
}
//determines the distance between two vectors
float Vector2::distance(const Vector2 & other) const
{
	//distance is found by finding the difference between the points
	//the difference is a vector that if added to one of the points will result in the other point
	float diffX = x - other.x;
	float diffY = y - other.y;
	//returns the magnitude of the vector
	return sqrt(diffX * diffX + diffY * diffY);
}
//determines the square of the distance between two vectors which allows for faster processing if the only necessity for the distance is to compare it to another
float Vector2::distanceSqr(const Vector2 & other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	return (diffX * diffX + diffY * diffY);
}
//scales the vector to unit-length
void Vector2::normalise()
{
	//by dividing the opposite and adjacent by the hypotenuse the vector becomes a unit of magnitude 1
	float mag = magnitude();
	x /= mag;
	y /= mag;
}

//allows for iteration of the array
float & Vector2::operator[](const int index)
{
	return data[index];
}
//allows float casting
Vector2::operator float*()
{
	return data;
}
//returns the inverse of the vector
Vector2 & Vector2::operator-()
{
	x = -x;
	y = -y;
	return *this;
}

//adds two vectors
Vector2 Vector2::operator+(const Vector2 & other) const
{
	return { x + other.x, y + other.y };
}
//adds a scalar to a vector
Vector2 Vector2::operator+(const float scalar) const
{
	return { x + scalar, y + scalar };
}

//subtracts a vector from a vector
Vector2 Vector2::operator-(const Vector2 & other) const
{
	return { x - other.x, y - other.y };
}
//subtracts a scalar from a vector
Vector2 Vector2::operator-(const float scalar) const
{
	return { x - scalar, y - scalar };
}

//multiplies two vectors
Vector2 Vector2::operator*(const Vector2 & other) const
{
	return { x * other.x, y * other.y };
}
//multiplies a vector by a scalar
Vector2 Vector2::operator*(const float scalar) const
{
	return { x * scalar, y * scalar };
}

//divides a vector by a vector
Vector2 Vector2::operator/(const Vector2 & other) const
{
	return { x / other.x, y / other.y };
}
//divides a vector by a scalar
Vector2 Vector2::operator/(const float scalar) const
{
	return { x / scalar, y / scalar };
}

//assigns a vector to the vector
Vector2 & Vector2::operator=(const Vector2 & other)
{
	x = other.x; y = other.y;
	return *this;
}
//assigns a scalar to the vector
Vector2 & Vector2::operator=(const float scalar)
{
	x = scalar; y = scalar;
	return *this;
}

//increments the vector by a vector
Vector2 & Vector2::operator+=(const Vector2 & other)
{
	x += other.x; y += other.y;
	return *this;
}
//increments the vector by a scalar
Vector2 & Vector2::operator+=(const float scalar)
{
	x += scalar; y += scalar;
	return *this;
}

//pre-increments the vector
Vector2 & Vector2::operator++()
{
	++x; ++y;
	return *this;
}
//post-increments the vector
Vector2 Vector2::operator++(int)
{
	const Vector2 old(*this);
	++(*this).x; ++(*this).y;
	return old;
}

//decrements the vector by a vector
Vector2 & Vector2::operator-=(const Vector2 & other)
{
	x -= other.x; y -= other.y;
	return *this;
}
//decrements the vector by a scalar
Vector2 & Vector2::operator-=(const float scalar)
{
	x -= scalar; y -= scalar;
	return *this;
}

//pre-decrements the vector
Vector2 & Vector2::operator--()
{
	--x; --y;
	return *this;
}
//post-decrements the vector
Vector2 Vector2::operator--(int)
{
	const Vector2 old(*this);
	--(*this).x; --(*this).y;
	return old;
}

//multiplies the vector by a vector 
Vector2 & Vector2::operator*=(const Vector2 & other)
{
	x *= other.x; y *= other.y;
	return *this;
}
//multiplies the vector by a scalar
Vector2 & Vector2::operator*=(const float scalar)
{
	x *= scalar; y *= scalar;
	return *this;
}

//divides the vector by a vector
Vector2 & Vector2::operator/=(const Vector2 & other)
{
	x /= other.x; y /= other.y;
	return *this;
}
//divides the vector by a scalar
Vector2 & Vector2::operator/=(const float scalar)
{
	x /= scalar; y /= scalar;
	return *this;
}

//checks if the vector is equal to another vector
bool Vector2::operator==(const Vector2 & other) const
{
	if (x == other.x && y == other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is equal to a scalar
bool Vector2::operator==(const float scalar) const
{
	if (x == scalar && y == scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is not equal to another vector
bool Vector2::operator!=(const Vector2 & other) const
{
	if (x != other.x || y != other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is not equal to a scalar
bool Vector2::operator!=(const float scalar) const
{
	if (x != scalar || y != scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than or equal to another vector
bool Vector2::operator<=(const Vector2 & other) const
{
	if (x <= other.x && y <= other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than or equal to a scalar
bool Vector2::operator<=(const float scalar) const
{
	if (x <= scalar && y <= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than or equal to another vector
bool Vector2::operator>=(const Vector2 & other) const
{
	if (x >= other.x && y >= other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than or equal to a scalar
bool Vector2::operator>=(const float scalar) const
{
	if (x >= scalar && y >= scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is less than another vector
bool Vector2::operator<(const Vector2 & other) const
{
	if (x < other.x && y < other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is less than a scalar
bool Vector2::operator<(const float scalar) const
{
	if (x < scalar && y < scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//checks if the vector is greater than another vector
bool Vector2::operator>(const Vector2 & other) const
{
	if (x > other.x && y > other.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//checks if the vector is greater than a scalar
bool Vector2::operator>(const float scalar) const
{
	if (x > scalar && y > scalar)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//adds a vector to a scalar
Vector2 operator+(const float scalar, const Vector2 & other)
{
	return { other.x + scalar, other.y + scalar };
}
//subtracts a vector from a scalar
Vector2 operator-(const float scalar, const Vector2 & other)
{
	return { other.x - scalar, other.y - scalar };
}
//multiplies a scalar by a vector
Vector2 operator*(const float scalar, const Vector2 & other)
{
	return { other.x * scalar, other.y * scalar };
}
//divides a scalar by a vector
Vector2 operator/(const float scalar, const Vector2 & other)
{
	return { other.x / scalar, other.y / scalar };
}