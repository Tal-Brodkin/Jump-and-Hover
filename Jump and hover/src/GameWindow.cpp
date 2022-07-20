#include "GameWindow.h"






GameWindow::GameWindow(ContactListener& listener, const int level_number) : m_world(std::make_unique<b2World>(Gravity)), m_level(level_number)
{
	GameManager::instance().buildGameObjects(m_world.get(), m_player, m_dynamic_objects, m_static_objects, level_number);
	m_world->SetContactListener(&listener);
}


void GameWindow::drawScreen(sf::RenderWindow& window)
{
	if (m_level == FirstLevel)
		help(window);

	for (auto& object : m_static_objects)
		object->draw(window);
	for (auto& object : m_dynamic_objects)
		object->draw(window);
	m_player.draw(window);
}


void GameWindow::updateScreen(const float time)
{
	m_world->Step(1 / 60.f, 8, 3);
	m_player.update(time);

	for (auto& object : m_dynamic_objects)
		object->update(time);

	for (auto& object : m_static_objects)
		object->update(time);
	
	std::erase_if(m_static_objects, [](const auto& object) { return object->isToDelete(); });
}

void GameWindow::movePlayer(const float x, const float y)
{
	m_player.move(x, y);
}

void GameWindow::playerHover(const bool hover)
{
	hover ? m_player.hover() : m_player.stopHover();
}

bool GameWindow::isPlayerOnGround() const
{
	return m_player.isOnGround();
}

void GameWindow::help(sf::RenderWindow& window)
{
	auto first_line = Resources::instance().makeText("Move with the left/right keys", 0, 12);
	auto second_line = Resources::instance().makeText("Jump/Hover with the Up/Space key", 0, 12);
	auto third_line = Resources::instance().makeText("Press again & hold to hover.", 0, 12);
	auto fourth_line = Resources::instance().makeText("Go back with B key", 0, 12);

	first_line.setPosition(40.f, 40.f);
	second_line.setPosition(40.f, 55.f);
	third_line.setPosition(40.f, 70.f);
	fourth_line.setPosition(40.f, 85.f);

	window.draw(first_line);
	window.draw(second_line);
	window.draw(third_line);
	window.draw(fourth_line);
}