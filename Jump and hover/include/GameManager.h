#pragma once
#include "Player.h"
#include "Wall.h"
#include "DynamicObject.h"
#include "StaticObject.h"
#include <vector>
#include "Enums.h"




class GameManager
{

	std::vector<std::string> m_map;

	bool m_key_pressed	= false;
	bool m_level_lost	= false;
	bool m_level_won	= false;
	bool m_repeat_level	= false;
	bool m_next_level	= false;

	int m_current_level	= 0;
	int m_top_level_achieved = 0;

	GameManager();
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void buildMap(const std::string&);
	void buildObject(char, 
					const sf::Vector2f&, 
					b2World*, 
					std::vector<std::unique_ptr<StaticObject>>&, 
					std::vector<std::unique_ptr<DynamicObject>>&, 
					Player&);

	sf::Vector2f convertPosition(const sf::Vector2f&, const sf::Vector2u&);

public:

	static GameManager& instance();
	~GameManager() = default;

	std::vector<sf::Sprite> biuldBackground();
	void buildGameObjects(b2World*, 
							Player&, 
							std::vector<std::unique_ptr<DynamicObject>>&, 
							std::vector<std::unique_ptr<StaticObject>>&, 
							const int);

	void reset();
	void updateLevelNumber(const int);
	void levelLost();
	void levelWon();
	void repeatLevel();
	void nextLevel();
	void updateKeyStatus(const bool);
	void loadData();
	void saveData();

	bool isGameLive() const;
	bool isLevelLost() const;
	bool isLevelWon() const;
	bool isKeyPressed() const;

	int currentLevel() const;
	int topLevelAchieved() const;
};