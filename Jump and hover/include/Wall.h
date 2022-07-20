#pragma once
#include "StaticObject.h"
#include "Factory.h"





class Wall : public StaticObject
{

	static bool m_registerit;

public:

	Wall(const sf::Vector2f&, b2World*);
	using StaticObject::StaticObject;

	virtual void update(const float) override {};
};