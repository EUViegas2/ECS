#include "Vec2.h"
#include<math.h>

Vec2::Vec2()
{

}

Vec2::Vec2(float xin, float yin)
	: x(xin), y(yin)
{

}

bool Vec2::operator==(const Vec2& rhs) const
{
	return this->x == rhs.x && this->y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const
{
	return this->x != rhs.x || this->y != rhs.y;
}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2& rhs) const
{
	return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 Vec2::operator/(const float val) const
{
	return Vec2(this->x / val, this->y / val);
}

Vec2 Vec2::operator*(const float val) const
{
	return Vec2(this->x * val, this->y * val);
}

Vec2 Vec2::operator+=(const Vec2& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}

Vec2 Vec2::operator-=(const Vec2& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return *this;
}

Vec2 Vec2::operator/=(const float val)
{
	this->x /= val;
	this->y /= val;
	return *this;
}

Vec2 Vec2::operator*=(const float val)
{
	this->x *= val;
	this->y *= val;
	return *this;
}

float Vec2::dist2(const Vec2& rhs) const { return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y); }
float Vec2::dist(const Vec2& rhs) const { return sqrtf(dist2(rhs)); }

void Vec2::normalize()
{
	float normal = dist(Vec2(0.0f, 0.0f));
	if (normal == 0) { x = 0; y = 0; }
	else { x /= normal; y /= normal; }
}

Vec2 Vec2::unitVec() const
{
	float length = dist(Vec2(0.0f, 0.0f));
	return length == 0 ? Vec2(0, 0) : Vec2(x / length, y / length);
}

void Vec2::setLength(const float norm)
{
	normalize();
	x *= norm;
	y *= norm;
}
