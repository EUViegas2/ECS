#pragma once

class Vec2
{


public:
	float x = 0;
	float y = 0;

	Vec2();
	Vec2(float xin, float yin);
	float getX() const { return this->x; }
	float getY() const { return this->y; }
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }

	bool operator == (const Vec2& rhs) const;
	bool operator != (const Vec2& rhs) const;

	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator - (const Vec2& rhs) const;
	Vec2 operator / (const float val) const;
	Vec2 operator * (const float val) const;

	Vec2 operator += (const Vec2& rhs);
	Vec2 operator -= (const Vec2& rhs);
	Vec2 operator /= (const float val);
	Vec2 operator *= (const float val);

	float dist(const Vec2& rhs) const;	
};

