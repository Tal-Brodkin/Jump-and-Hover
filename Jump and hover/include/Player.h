#pragma once
#include "DynamicObject.h"
#include "HoverBar.h"
#include "Factory.h"
#include "Resources.h"
#include "Enums.h"



class Player : public DynamicObject
{
	bool m_dead = false;
	bool m_hovering = false;
	bool m_on_ground = false;

	HoverBar m_hover_bar;

	static bool m_registerit;

	void update_hover(const float);

public:

	using DynamicObject::DynamicObject;
	Player(const sf::Vector2f&, b2World*);

	bool isDead() const;
	bool isOnGround() const;
	bool isHovering() const;
	
	void dead();
	void hover();
	void stopHover();
	void resetHover();
	void onGround(const bool);
	void draw(sf::RenderWindow&);
	void move(const float, const float);

	virtual void update(const float) override;
};

