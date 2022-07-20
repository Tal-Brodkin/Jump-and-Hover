#include "Menu.h"
#include "Controller.h"


namespace
{
	int find_selection(std::vector<Button>& data)
	{
		for (int i = 0; i < data.size(); i++)
			if (data[i].isSelected())
				return i;
	}

	void select_level(std::vector<Button>& data, Menu* object)
	{
		int selection = find_selection(data);
		if (selection > GameManager::instance().topLevelAchieved())
		{
			Resources::instance().playSound(ErrorSelectSound);
			return;
		}
		Resources::instance().playSound(MenuClickSound);
		GameManager::instance().updateLevelNumber(selection);
		object->loadLevel(selection);
		if (GameManager::instance().currentLevel() == LastLevel)
			object->end_screen();
		object->createLevels();
	}

	void make_select(std::vector<Button>& data, Menu* object)
	{
		int selection = find_selection(data);
		Resources::instance().playSound(MenuClickSound);
		switch (selection)
		{
			case 0:
				object->drawMenu(object->getLevels(), select_level);
				break;
			case 1:
				Resources::instance().changeVolume();
				break;
			case 2:
				object->exit();
				break;
		}
	}
}



Menu::Menu() : m_background(GameManager::instance().biuldBackground()), m_window(sf::RenderWindow(sf::VideoMode(Width, Height), JumpAndHover, sf::Style::Close))
{
	m_window.setFramerateLimit(Frames);
	try
	{
		GameManager::instance().loadData();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}
	createButtons();
	createLevels();
}

void Menu::run()
{
	Resources::instance().playMusic();
	this->drawMenu(m_buttons, make_select);
}


void Menu::drawMenu(std::vector<Button>& data, void(*select_func)(std::vector<Button>&, Menu*))
{
	while (m_window.isOpen() && !m_exit)
	{
		m_window.clear();
		for (auto& object : m_background)
			m_window.draw(object);
		for (auto& object : data)
			m_window.draw(object.body);
		title();
		m_window.display();

        auto event = sf::Event();
        while (m_window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
				GameManager::instance().saveData();
				m_window.close();
                break;
			case sf::Event::KeyReleased:
				GameManager::instance().updateKeyStatus(UnPressed);
				break;
            }
        }

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))			
			moveSelect(Back, data);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))		
			moveSelect(Forward, data);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))	
		{
			if (!GameManager::instance().isKeyPressed())
			{
				GameManager::instance().updateKeyStatus(Pressed);
				select_func(data, this);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
		{
			if (!GameManager::instance().isKeyPressed())
			{
				GameManager::instance().updateKeyStatus(Pressed);
				GameManager::instance().saveData();
				break;
			}
		}
	}
}


void Menu::exit()
{
	m_exit = true;
	GameManager::instance().saveData();
}

void Menu::loadLevel(const int level_number)
{
	try
	{
		Controller controller;
		controller.run(m_window, m_background, level_number);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		GameManager::instance().saveData();
	}
	catch (...)
	{
		std::cout << UnknownError << "\n";
		GameManager::instance().saveData();
	}
}

std::vector<Button>& Menu::getLevels()
{
	return m_levels;
}


void Menu::title()
{
	auto& font = Resources::instance().getFont(0);

	sf::Text title;
	title.setFont(font);
	title.setStyle(sf::Text::Bold);
	title.setString(JumpAndHover);
	title.setCharacterSize(38);
	title.setFillColor(ThemeColor);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(1);
	title.setOrigin(title.getGlobalBounds().width / 2.0f, title.getGlobalBounds().height / 2.0f);
	title.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 4.0f);

	m_window.draw(title);
}


void Menu::createButtons()
{
	auto size = sf::Vector2f(Width, Height);

	auto start_button = makeButton(StartButton, 0);
	start_button.setPosition(size.x / 2.0f, size.y / 2.2f);
	start_button.selected = true;
	start_button.body.setOutlineColor(sf::Color(0, 171, 255, 255));

	auto music_button = makeButton(MusicButton, 0);
	music_button.setPosition(size.x / 2.0f, size.y / 1.8f);

	auto exit_button = makeButton(ExitButton, 0);
	exit_button.setPosition(size.x / 2.0f, size.y / 1.5f);

	m_buttons.push_back(start_button);
	m_buttons.push_back(music_button);
	m_buttons.push_back(exit_button);
}

void Menu::createLevels()
{
	m_levels.clear();
	int current_level = GameManager::instance().currentLevel();
	int top_level = GameManager::instance().topLevelAchieved();
	int level_number = 0;

	for (float row = Height / 2.3f; row <= Height / 1.4f; row += Height / 6.f)
	{
		for (float col = Width / 3.2f; col <= Width / 1.4f; col += Width / 8.f)
		{
			Button button;

			if (level_number <= top_level)
				button = makeButton(std::to_string(level_number + 1), 1, 60);
			else
				button = makeButton(LockedLevel, 1, 60, sf::Color::Red);

			button.setPosition(col, row);
			m_levels.push_back(button);
			level_number++;
		}
	}

	m_levels[current_level].selected = true;
	m_levels[current_level].body.setOutlineColor(ThemeColor);
}


Button Menu::makeButton(const std::string& string, const int font_index, const int size, const sf::Color& color)
{
	auto text = Resources::instance().makeText(string, font_index, size, color);
	text.setOrigin(text.getGlobalBounds().width / 2.0f, text.getGlobalBounds().height / 2.0f);
	auto button = Button(text, false);

	return button;
}


void Menu::moveSelect(const int dir, std::vector<Button>& data)
{
	if (!GameManager::instance().isKeyPressed())
	{
		Resources::instance().playSound(MenuClick2Sound);

		for (size_t i = 0; i < data.size(); i++)
		{
			if (data[i].isSelected())
			{
				if (i + dir >= 0 && i + dir < data.size())
				{
					data[i].selected = false;
					data[i + dir].selected = true;

					for (auto& button : data)
					{
						if (button.selected)
							button.body.setOutlineColor(ThemeColor);
						else
							button.body.setOutlineColor(sf::Color::Black);
					}
				}
				break;
			}
		}

		GameManager::instance().updateKeyStatus(Pressed);
	}
}

void Menu::end_screen()
{
	auto first_line = Resources::instance().makeText("Congratulations!!!", 0, 26, ThemeColor);
	auto second_line = Resources::instance().makeText("You've finished the game.", 0, 22);
	auto third_line = Resources::instance().makeText("Press B to go back", 0, 18);

	first_line.setOrigin(first_line.getGlobalBounds().width / 2.0f, first_line.getGlobalBounds().height / 2.0f);
	second_line.setOrigin(second_line.getGlobalBounds().width / 2.0f, second_line.getGlobalBounds().height / 2.0f);
	third_line.setOrigin(third_line.getGlobalBounds().width / 2.0f, third_line.getGlobalBounds().height / 2.0f);

	first_line.setPosition(250.f, 150.f);
	second_line.setPosition(250.f, 200.f);
	third_line.setPosition(250.f, 240.f);

	m_window.clear();
	for (auto& object : m_background)
		m_window.draw(object);
	m_window.draw(first_line);
	m_window.draw(second_line);
	m_window.draw(third_line);
	m_window.display();

	while (m_window.isOpen())
	{
		auto event = sf::Event();
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GameManager::instance().saveData();
				m_window.close();
				break;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			break;
	}
}
