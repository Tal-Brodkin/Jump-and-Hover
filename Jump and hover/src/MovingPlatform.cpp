#include "MovingPlatform.h"




bool MovingPlatform::m_registerit = Factory<DynamicObject>::registerIt(MovingPlatformObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<DynamicObject> { return std::make_unique<MovingPlatform>(position, world); });




MovingPlatform::MovingPlatform(const sf::Vector2f& position_vec, b2World* world) : DynamicObject(Resources::instance().getTexture(MovingPlatformTexture),
																								sf::Vector2u({ 32, 32 }),
																								position_vec,
																								std::vector<int>{ 4 })
{
	auto& texture = Resources::instance().getTexture(PlatformTexture);
	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((position.x + width / 2) / Scale, (position.y + hieght) / Scale);
	bodyDef.type = b2_kinematicBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);
	
	b2PolygonShape Shape;
	Shape.SetAsBox((width / 2.f) / Scale, (hieght / 2.f / 4.f) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);
	
	m_phisical_body = body;
}

void MovingPlatform::canNotMove()
{
	m_can_move = false;
}

bool MovingPlatform::canMove() const
{
	return m_can_move;
}

void MovingPlatform::update(const float time)
{
	this->updateAnimation(time);
	this->updateDeceleration(PlatformFrictionDecrease);
	this->updatePosition(Scale * m_phisical_body->GetPosition().x - 16, Scale * m_phisical_body->GetPosition().y - 25);
}
