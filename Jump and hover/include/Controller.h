#pragma once
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "Enums.h"
#include "GameManager.h"



class Controller 
{

	void keyboardEvents(sf::RenderWindow&, GameWindow&, const float, bool&);
	void drawAndUpdate(sf::RenderWindow&, GameWindow&, const std::vector<sf::Sprite>&, const float);
	void checkLevelStatus(float&, const float, int&, bool&);

public:

	Controller() = default;

	void run(sf::RenderWindow&, const std::vector<sf::Sprite>&, const int);
};