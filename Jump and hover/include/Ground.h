#pragma once
#include "StaticObject.h"
#include "Factory.h"





class Ground : public StaticObject
{

	static bool m_registerit;

public:

	Ground(const sf::Vector2f&, b2World*);

	virtual void update(const float) override {};
};