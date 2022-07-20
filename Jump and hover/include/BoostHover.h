#pragma once
#include "StaticObject.h"
#include "Factory.h"





class BoostHover : public StaticObject
{
	static bool m_registerit;

public:

	BoostHover(const sf::Vector2f&, b2World*);
	~BoostHover();

	virtual void update(const float) override;
};