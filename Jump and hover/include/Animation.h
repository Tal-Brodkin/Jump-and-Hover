#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Enums.h"
#include <iostream>



class Animation
{
	sf::IntRect m_rect;
	std::vector<int> m_frames;
	int m_current_frames;
	int m_current_rect;
	float m_elapsed_time;
	Orientation m_orientation = Orientation::Normal;

	void updateRectLeft(const float);
	void updateRectTop(const int, sf::Sprite&);
	void changeDirectionMidair(const float);

public:

	Animation() = default;
	Animation(const sf::IntRect& rect, const std::vector<int>&);

	void update(sf::Sprite&, const float, const b2Vec2& = {0, 0}, const bool = true);
};