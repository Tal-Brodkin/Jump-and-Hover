#include "FallingPlatform.h"




bool FallingPlatform::m_registerit = Factory<DynamicObject>::registerIt(FallingPlatformObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<DynamicObject> { return std::make_unique<FallingPlatform>(position, world); });




FallingPlatform::FallingPlatform(const sf::Vector2f& position_vec, b2World* world) : DynamicObject(Resources::instance().getTexture(FalingPlatformTexture),
																									sf::Vector2u({ 32, 32 }),
																									position_vec,
																									std::vector<int>{ 4 })
{
	auto& texture = Resources::instance().getTexture(PlatformTexture); // need to change
	auto width = texture.getSize().x;
	auto hieght = texture.getSize().y;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2((position.x + width / 2) / Scale, (position.y + hieght) / Scale);
	bodyDef.type = b2_kinematicBody;
	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape Shape;
	Shape.SetAsBox((width / 2.f) / Scale, (hieght / 2.f / 4.f) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.shape = &Shape;
	FixtureDef.density = 1;
	body->CreateFixture(&FixtureDef);

	m_phisical_body = body;
}

void FallingPlatform::makeFall()
{
	m_fall_down = true;
}

void FallingPlatform::update(const float time)
{
	this->updateAnimation(time);
	this->updatePosition(Scale * m_phisical_body->GetPosition().x - 16, Scale * m_phisical_body->GetPosition().y - 25);

	if (m_fall_down)
	{
		m_elapsed_time += time;

		if (m_elapsed_time > FallDownDelay)
		{
			m_phisical_body->SetType(b2_dynamicBody); 
			m_visual_body.setTexture(Resources::instance().getTexture(FalingPlatformOffTexture));
			m_animaiotn = Animation(sf::IntRect({ 0, 0, 32, 32 }), std::vector<int>{ 1 });
			m_phisical_body->GetFixtureList()->SetSensor(true);
		}
	}
}
