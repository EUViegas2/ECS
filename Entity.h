#pragma once
#include "Component.h"
#include <memory>
#include <string>



class Entity
{
	friend class EntityManager;

	bool		m_active	{ true };
	size_t		m_id		{ 0 };
	std::string m_tag		{ "default" };

	//Constructor and Destructor
	Entity(const size_t id, const std::string& tag);

public:
	//component pointers
	std::shared_ptr<cTransform> cTransform;
	std::shared_ptr<cShape>		cShape;
	std::shared_ptr<cCollision> cCollision;
	std::shared_ptr<cInput>		cInput;
	std::shared_ptr<cScore>		cScore;
	std::shared_ptr<cLifespan>	cLifespan;

	//private member access functions
	bool isActive() const;
	const std::string& tag() const;
	const size_t id() const;
	void destroy();

	Entity(){}
};