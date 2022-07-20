#include "Player.h"
#include "GameManager.h"



bool Player::m_registerit = Factory<Player>::registerIt(PlayerObject, [](const sf::Vector2f& position, b2World* world) -> std::unique_ptr<Player> { return std::make_unique<Player>(position, world); });





Player::Player(const sf::Vector2f& position_vec, b2World* world) : DynamicObject(Resources::instance().getTexture(PlayerTexture),  // Tetxure
																				 sf::Vector2u({32, 32}),							// Texture's size
																				 position_vec,										// position
																			     std::vector<int>{ 11, 12, 1, 1, 1 })				// animation info (frames)
{
	this->setOrigin(16.f, 16.f);
	
	auto width = 32u;
	auto hieght = 32u;
	auto position = this->convertPosition(position_vec, { width, hieght });

	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(position.x / Scale, position.y / Scale);
	BodyDef.type = b2_dynamicBody;
	BodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
	b2Body* body = world->CreateBody(&BodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape Shape;
	Shape.SetAsBox((width / 2.f - 1) / Scale, (hieght / 2.f - 1) / Scale);
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 0.f;
	FixtureDef.shape = &Shape;
	body->CreateFixture(&FixtureDef);
	
	m_phisical_body = body;
}



bool Player::isDead() const
{
	return m_dead;
}

bool Player::isOnGround() const
{
	return m_on_ground;
}

bool Player::isHovering() const
{
	return m_hovering;
}

void Player::resetHover()
{
	m_hover_bar.reset();
}

void Player::dead()
{
	Resources::instance().playSound(PlayerDead2Sound);
	m_dead = true;
	this->updateLinearVelocity({ 0, 0 });
	this->moveVertically(-13);
	m_phisical_body->SetFixedRotation(false);
	m_phisical_body->ApplyAngularImpulse(2.f, true);
	m_phisical_body->GetFixtureList()->SetSensor(true);
	GameManager::instance().levelLost();
}

void Player::move(const float x, const float y)
{
	if (this->m_phisical_body != nullptr)
	{
		if (x != 0)
			this->moveHorizontally(x);
		if (y != 0)
		{
			Resources::instance().playSound(PlayerJumpSound);
			this->gravityOn();
			this->moveVertically(y);
			this->onGround(false);
		}
	}
	else
		throw std::exception(PlayerObjectMissing.c_str());
}

void Player::update(const float time)
{
	if (this->m_phisical_body != nullptr)
	{
		
		this->updatePosition(Scale * m_phisical_body->GetPosition().x, Scale * m_phisical_body->GetPosition().y);
		this->updateRotation(180 / b2_pi * m_phisical_body->GetAngle());
		this->update_hover(time);
		this->updateAnimation(time, m_on_ground, this->getLinearVelocity());
		this->updateDeceleration(PlayerFrictionDecrease);
		

		if (this->getLinearVelocity().y != 0)
			m_on_ground = false;
	}
	else
		throw std::exception(PlayerObjectMissing.c_str());
}

void Player::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);

	if (m_hovering)
		m_hover_bar.draw(window);
}

void Player::hover()
{
	if (this->m_phisical_body != nullptr)
	{
		if (!m_hover_bar.isTimeOver() && !m_dead)
		{
			m_hovering = true;
			this->gravityOff();
		}
	}
}

void Player::stopHover()
{
	if (this->m_phisical_body != nullptr)
	{
		m_hovering = false;
		this->gravityOn();
	}
}

void Player::onGround(const bool state)
{
	m_on_ground = state;
}


void Player::update_hover(const float time)
{
	if (m_hovering)
	{
		m_hover_bar.update(time, this->getVisualBodyPosition());

		if (m_hover_bar.isTimeOver())
		{
			stopHover();
		}
	}
	else if (isOnGround())
		m_hover_bar.reset();
}


