#include "BoostHover.h"





bool BoostHover::m_registerit = Factory<StaticObject>::registerIt(BoostHoverObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<StaticObject> { return std::make_unique<BoostHover>(position, world); });






BoostHover::BoostHover(const sf::Vector2f& position_vec, b2World* world) : StaticObject(Resources::instance().getTexture(AppleTetxture),
																						sf::Vector2u({ 32, 32 }),
																						position_vec,
																						std::vector<int>{ 17 })
{
	auto width = 32u;
	auto hieght = 32u;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((position.x + width / 2) / Scale, (position.y + hieght / 2) / Scale);
	bodyDef.type = b2_staticBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((width / 4.f) / Scale, (hieght / 4.f) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.isSensor = true;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);

	m_phisical_body = body;
}

BoostHover::~BoostHover()
{
	this->m_phisical_body->GetWorld()->DestroyBody(m_phisical_body);
}

void BoostHover::update(const float time)
{
	this->updateAnimation(time);
}
