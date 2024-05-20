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

float Vec2::dist(const Vec2& rhs) const
{
	float dx = x + rhs.x;
	float dy = y + rhs.y;
	return sqrt(dx * dx + dy * dy);
}
