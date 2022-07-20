#include "HoverBar.h"




HoverBar::HoverBar() : m_sprite(Resources::instance().getTexture(HoverBarTexture)), m_rect({0, 0, 35, 6})
{
	m_sprite.setTextureRect(m_rect);
}

bool HoverBar::isTimeOver() const
{
	return m_time_over;
}

void HoverBar::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void HoverBar::update(const float time, const sf::Vector2f& player_posiotn)
{
	auto bar_position = sf::Vector2f(player_posiotn.x - 20, player_posiotn.y - 20);
	m_sprite.setPosition(bar_position);
	m_sprite.setTextureRect(m_rect);

	m_elapsed_time += time;
	m_total_elapsed_time += time;

	if (m_total_elapsed_time <= m_duration)
	{
		if (!m_hover_cycle)
		{
			
			m_rect.top = (m_rect.top + m_rect.height) % (m_rect.height * 35);
			m_elapsed_time = 0;
			if (m_rect.top == 204)
				m_hover_cycle = true;
		}
	}
	else
	{
		m_time_over = true;
	}
}

void HoverBar::reset()
{
	m_rect.top = 0;
	m_total_elapsed_time = 0;
	m_time_over = false;
	m_hover_cycle = false;
}
