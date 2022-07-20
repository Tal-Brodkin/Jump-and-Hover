#include "Ground.h"




bool Ground::m_registerit = Factory<StaticObject>::registerIt(GroundObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<StaticObject> { return std::make_unique<Ground>(position, world); });




Ground::Ground(const sf::Vector2f& position_vec, b2World* world) : StaticObject(Resources::instance().getTexture(WallTexture),
																				Resources::instance().getTexture(WallTexture).getSize(),
																				position_vec)
{
	auto& texture = Resources::instance().getTexture(WallTexture);
	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);

	b2Vec2 v0((position.x - width) / Scale, position.y / Scale);
	b2Vec2 v1(position.x / Scale, position.y / Scale);
	b2Vec2 v2((position.x + width) / Scale, position.y / Scale);
	b2Vec2 v3((position.x + width * 2) / Scale, position.y / Scale);
	b2Vec2 v4(position.x / Scale, position.y / Scale);
	b2Vec2 v5((position.x) / Scale, (position.y + hieght) / Scale);
	b2Vec2 v6((position.x + width) / Scale, position.y / Scale);
	b2Vec2 v7((position.x + width) / Scale, (position.y + hieght) / Scale);
	b2Vec2 v8(position.x / Scale, (position.y + hieght) / Scale);
	b2Vec2 v9((position.x + width) / Scale, (position.y + hieght) / Scale);

	b2EdgeShape edge1;
	b2EdgeShape edge2;
	b2EdgeShape edge3;
	b2EdgeShape edge4;

	edge1.SetOneSided(v0, v1, v2, v3);
	edge2.SetTwoSided(v4, v5);
	edge3.SetTwoSided(v6, v7);
	edge4.SetTwoSided(v8, v9);

	b2FixtureDef FixtureDef1;
	b2FixtureDef FixtureDef2;
	b2FixtureDef FixtureDef3;
	b2FixtureDef FixtureDef4;

	FixtureDef1.shape = &edge1;
	FixtureDef2.shape = &edge2;
	FixtureDef3.shape = &edge3;
	FixtureDef4.shape = &edge4;
	body->CreateFixture(&FixtureDef1);
	body->CreateFixture(&FixtureDef2);
	body->CreateFixture(&FixtureDef3);
	body->CreateFixture(&FixtureDef4);

	m_phisical_body = body;
}
