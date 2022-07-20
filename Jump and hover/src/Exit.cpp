#include "Exit.h"



bool Exit::m_registerit = Factory<StaticObject>::registerIt(ExitObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<StaticObject> { return std::make_unique<Exit>(position, world); });





Exit::Exit(const sf::Vector2f& position_vec, b2World* world) 
{
	auto& texture = Resources::instance().getTexture(ExitTexture);
	auto position = this->convertPosition(position_vec, { 32u, 32u });

	sf::Sprite sprite(texture);
	sprite.setPosition(position);
	m_visual_body = sprite;

	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((position.x + width / 3.f) / Scale, (position.y  + hieght / 1.5f) / Scale);
	bodyDef.type = b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((width / 11.f) / Scale, (hieght / 4.f) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.isSensor = true;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);

	m_phisical_body = body;
}



void Exit::achieved()
{
	Resources::instance().playSound(LevelWonSound);
	GameManager::instance().levelWon();
	m_visual_body.setTexture(Resources::instance().getTexture(ExitAchievedTexture));
	m_achieved = true;
	m_animaiotn = Animation(sf::IntRect({ 0, 0, 64, 64 }), std::vector<int>{ 36 });
}

bool Exit::isAchieved()
{
	return m_achieved;
}

void Exit::update(const float time)
{
	if (m_achieved)
	{
		this->updateAnimation(time);
	}
}
