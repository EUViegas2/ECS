#pragma once
#include "Vec2.h"
#include<SFML/Graphics.hpp>



class cTransform
{
public:
	Vec2	pos		=	{ 0,0 };
	Vec2	vel		=	{ 0,0 };
	float	angle		{ 0 };
	cTransform(){}
	cTransform(const Vec2& p, const Vec2& v, float a)
		: pos(p), vel(v), angle(a) {}


};

class cShape
{
public:
	sf::CircleShape		circle;

	cShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness) 
		: circle(radius, points)
	{
		circle.setFillColor(fill);
		circle.setOutlineColor(outline);
		circle.setOutlineThickness(thickness);
		circle.setOrigin(radius, radius);
	}

};

class cCollision
{
public:
	float radius{ 0 };
	cCollision(float r)
		: radius(r) {}
};

class cScore
{
public:
	int score{ 0 };
	cScore(int s)
		: score(s) {}
};

class cLifespan
{
public:
	int remaining	{ 0 };
	int total		{ 0 };
	cLifespan(int total)
		:remaining(total), total(total) {}
};

class cInput
{
public:
	bool up		{ false };
	bool left	{ false };
	bool right	{ false };
	bool down	{ false };
	bool shoot	{ false };

	cInput() {}
};