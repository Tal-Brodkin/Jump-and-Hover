#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameManager.h"
#include "Resources.h"





struct Button
{
	sf::Text body;
	bool selected;

	bool isSelected() { return selected; };
	void setPosition(const float x, const float y) { body.setPosition(x, y); };
};


class Menu
{
protected:

	sf::RenderWindow m_window;
	std::vector<sf::Sprite> m_background;
	std::vector<Button> m_buttons;
	std::vector<Button> m_levels;

	bool m_exit = false;
	bool m_key_pressed = false;

	void title();
	void createButtons();
	void moveSelect(const int, std::vector<Button>&);

	Button makeButton(const std::string&, const int, const int = 24, const sf::Color & = sf::Color::White);

public:

	Menu();

	void run();
	void createLevels();
	void loadLevel(const int);
	void drawMenu(std::vector<Button>&, void(*select_func)(std::vector<Button>&, Menu*));
	void end_screen();
	void exit();

	std::vector<Button>& getLevels();
};

