#include "Animation.h"



Animation::Animation(const sf::IntRect& rect, const std::vector<int>& frames) :
																			m_rect(rect),
																			m_frames(frames), 
																			m_current_frames(1),
																			m_current_rect(0),
																			m_elapsed_time(0)
{
}



void Animation::update(sf::Sprite& sprite, const float time, const b2Vec2& velocity, const bool onGround)
{


	if (velocity.x > 0 && velocity.y == 0) // moving right
	{
		changeDirectionMidair(velocity.x);
		onGround ? updateRectTop(1, sprite) : updateRectTop(4, sprite);
	}
	else if (velocity.x < 0 && velocity.y == 0) // moving left
	{
		changeDirectionMidair(velocity.x);
		onGround ? updateRectTop(1, sprite) : updateRectTop(4, sprite);
	}
	else if (velocity.y < 0) // moving up
	{
		updateRectTop(2, sprite);
		changeDirectionMidair(velocity.x);
	}
	else if (velocity.y > 0) // moving down
	{
		updateRectTop(3, sprite);
		changeDirectionMidair(velocity.x);
	}
	else // idle
	{
		onGround ? updateRectTop(0, sprite) : updateRectTop(4, sprite);
	}

	updateRectLeft(time);
	sprite.setTextureRect(m_rect);
}

void Animation::updateRectLeft(const float time)
{
	m_elapsed_time += time;

	if (m_elapsed_time >= SwitchTime)
	{
		m_rect.left = (m_rect.left + m_rect.width) % (m_rect.width * m_current_frames);
		m_elapsed_time -= SwitchTime;
	}
}

void Animation::updateRectTop(const int index, sf::Sprite& sprite)
{
	m_rect.top = index * m_rect.width;
	m_current_frames = m_frames[index];
	sprite.setScale(float(m_orientation), 1.f);

	if (m_current_rect != m_rect.top)
	{
		m_rect.left = 0;
		m_current_rect = m_rect.top;
	}
}

void Animation::changeDirectionMidair(const float value)
{
	if (abs(value) < 1.f)
		return;

	if (value > 0)
		m_orientation = Orientation::Normal;
	else if (value < 0)
		m_orientation = Orientation::Reverse;
}
