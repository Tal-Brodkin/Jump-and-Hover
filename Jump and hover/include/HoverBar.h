#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "Enums.h"




class HoverBar
{
	bool m_time_over = false;
	bool m_hover_cycle = false;
	float m_duration = HoverTime;

	sf::Sprite m_sprite;
	sf::IntRect m_rect;
	
	float m_elapsed_time = 0.f;
	float m_total_elapsed_time = 0.f;

public:

	HoverBar();

	bool isTimeOver() const;

	void draw(sf::RenderWindow&);
	void update(const float, const sf::Vector2f&);
	void reset();
};