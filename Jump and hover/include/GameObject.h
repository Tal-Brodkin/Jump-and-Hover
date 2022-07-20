#pragma once
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "Animation.h"
#include <iostream>
#include <Windows.h>
#include "Resources.h"
#include "Enums.h"
#include <typeinfo>





class GameObject
{
protected:

	sf::Sprite m_visual_body;
	b2Body* m_phisical_body = nullptr;
	Animation m_animaiotn;

	void generateSprite(const sf::Texture& texture, const sf::Vector2u&, const sf::Vector2f&);

public:

	GameObject() = default;
	GameObject(const sf::Texture&, const sf::Vector2u&, const sf::Vector2f&, const std::vector<int>&);	// for animetaed objects
	GameObject(const sf::Texture&, const sf::Vector2u&, const sf::Vector2f&);							// for non-animetaed objects
	GameObject(const GameObject& other);	// copy c-tor
	virtual ~GameObject() = default;

	b2Vec2 getLinearVelocity() const;
	sf::Vector2f getVisualBodyPosition() const;
	sf::Vector2f convertPosition(const sf::Vector2f&, const sf::Vector2u&);

	void draw(sf::RenderWindow&);
	void updatePosition(const float, const float);
	void updateRotation(const float);
	void updateAnimation(const float, const bool = true, const b2Vec2& = {0,0});
	void updateDeceleration(const float);
	void updateLinearVelocity(const b2Vec2&);
	void setOrigin(const float, const float);

	void moveHorizontally(const float);
	void moveVertically(const float);

	void gravityOff();
	void gravityOn();

	GameObject& operator=(GameObject& other);
	void swap(GameObject& other);
};