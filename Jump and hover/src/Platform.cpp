#include "Platform.h"




bool Platform::m_registerit = Factory<StaticObject>::registerIt(PlatformObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<StaticObject> { return std::make_unique<Platform>(position, world); });




Platform::Platform(const sf::Vector2f& position_vec, b2World* world) : StaticObject(Resources::instance().getTexture(PlatformTexture), 
																				sf::Vector2u({32, 32}),
																				position_vec)
{
	auto& texture = Resources::instance().getTexture(PlatformTexture);
	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;	
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);

	b2Vec2 v0((position.x - width) / Scale, (position.y + hieght) / Scale);
	b2Vec2 v1(position.x / Scale, (position.y + hieght - 5)/ Scale);
	b2Vec2 v2((position.x + width) / Scale, (position.y + hieght - 5) / Scale);
	b2Vec2 v3((position.x + width * 2) / Scale, (position.y + hieght) / Scale);

	b2EdgeShape edge1;
	b2EdgeShape edge2;

	edge1.SetOneSided(v0, v1, v2, v3);
	edge2.SetTwoSided(v1, v2);

	b2FixtureDef FixtureDef1;
	b2FixtureDef FixtureDef2;
	FixtureDef1.density = 0.f;
	FixtureDef1.shape = &edge1;
	FixtureDef2.friction = 0;
	FixtureDef2.shape = &edge2;
	body->CreateFixture(&FixtureDef1);
	body->CreateFixture(&FixtureDef2);

	m_phisical_body = body;
}