#pragma once
#include "DynamicObject.h"
#include "StaticObject.h"
#include "Resources.h"
#include "Player.h"
#include <vector>
#include "Enums.h"
#include <string>
#include "GameManager.h"
#include "ContactListener.h"
#include "MovingPlatform.h"
#include "Menu.h"




class GameWindow
{
	int m_level;
	Player m_player;
	std::unique_ptr<b2World> m_world;
	std::vector<std::unique_ptr<DynamicObject>> m_dynamic_objects;
	std::vector<std::unique_ptr<StaticObject>> m_static_objects;

	void help(sf::RenderWindow&);

public:

	GameWindow(ContactListener&, const int);

	void drawScreen(sf::RenderWindow&);
	void updateScreen(const float);
	void movePlayer(const float, const float);
	void playerHover(const bool);

	bool isPlayerOnGround() const;
};