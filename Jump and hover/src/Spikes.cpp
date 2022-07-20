#include "Spikes.h"






bool Spikes::m_registerit = Factory<StaticObject>::registerIt(SpikesObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<StaticObject> { return std::make_unique<Spikes>(position, world); });





Spikes::Spikes(const sf::Vector2f& position_vec, b2World* world) : StaticObject(Resources::instance().getTexture(SpikesTexture),
																				Resources::instance().getTexture(SpikesTexture).getSize(),
																				position_vec)
{
	auto& texture = Resources::instance().getTexture(SpikesTexture);
	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((position.x + width / 2) / Scale, (position.y + hieght) / Scale);
	bodyDef.type = b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((width / 3.f) / Scale, (hieght / 8.f) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;
	FixtureDef.friction = 1;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);
}


