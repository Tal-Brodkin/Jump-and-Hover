#include "GameObject.h"





	
GameObject::GameObject(const sf::Texture& texture, 
						const sf::Vector2u& texture_size, 
						const sf::Vector2f& position_vec, 
						const std::vector<int>& frames) : m_animaiotn(sf::IntRect({ 0, 0, (int)texture_size.x, (int)texture_size.y }), frames)
{
	auto position = convertPosition(position_vec, texture_size);
	generateSprite(texture, texture_size, position);
}


GameObject::GameObject(const sf::Texture& texture, const sf::Vector2u& texture_size, const sf::Vector2f& position_vec)
{
	auto position = convertPosition(position_vec, texture_size);
	generateSprite(texture, texture_size, position);
}


GameObject::GameObject(const GameObject& other)
	: m_visual_body(other.m_visual_body),
	m_phisical_body(other.m_phisical_body),
	m_animaiotn(other.m_animaiotn)
{
	if (m_phisical_body != nullptr)
		m_phisical_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}



b2Vec2 GameObject::getLinearVelocity() const
{
	return m_phisical_body->GetLinearVelocity();
}

sf::Vector2f GameObject::getVisualBodyPosition() const
{
	return m_visual_body.getPosition();
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_visual_body);
}


void GameObject::updatePosition(const float x, const float y)
{
	m_visual_body.setPosition(x, y);
}


void GameObject::updateRotation(const float angel)
{
	m_visual_body.setRotation(angel);
}


void GameObject::updateAnimation(const float time, const bool isOnGround, const b2Vec2& velocity)
{
	m_animaiotn.update(m_visual_body, time, velocity, isOnGround);
}

void GameObject::updateDeceleration(const float  friction_decrease)
{
	auto velocity = m_phisical_body->GetLinearVelocity();

	if (velocity.x)
	{
		velocity.x *= friction_decrease;
		if (abs(velocity.x) < 0.3f)
			velocity.x = 0;
	}
	m_phisical_body->SetLinearVelocity({ velocity.x, velocity.y });
}

void GameObject::moveHorizontally(const float x)
{
	float velChange = x - m_phisical_body->GetLinearVelocity().x;
	float h_impulse = m_phisical_body->GetMass() * velChange;

	m_phisical_body->ApplyLinearImpulseToCenter(b2Vec2(h_impulse, 0), true);
}

void GameObject::moveVertically(const float y)
{
	float v_impulse = m_phisical_body->GetMass() * y;
	m_phisical_body->ApplyLinearImpulseToCenter(b2Vec2(0, v_impulse), true);
}

void GameObject::gravityOn()
{
	m_phisical_body->SetGravityScale(1.f);
	m_phisical_body->SetAwake(true);
}


void GameObject::updateLinearVelocity(const b2Vec2& velocity)
{
	m_phisical_body->SetLinearVelocity(velocity);
}


GameObject& GameObject::operator=(GameObject& other)
{
	auto temp = other;
	temp.swap(*this);
	if (m_phisical_body != nullptr)
		m_phisical_body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
	return *this;
}

void GameObject::swap(GameObject& other)
{
	std::ranges::swap(m_visual_body, other.m_visual_body);
	std::ranges::swap(m_phisical_body, other.m_phisical_body);
	std::ranges::swap(m_animaiotn, other.m_animaiotn);
}


void GameObject::gravityOff()
{
	m_phisical_body->SetLinearVelocity({ 0,0 });
	m_phisical_body->SetGravityScale(0.f);
}

void GameObject::generateSprite(const sf::Texture& texture, const sf::Vector2u& texture_size, const sf::Vector2f& position)
{
	sf::Sprite sprite(texture);
	sprite.setPosition(position);
	sprite.setTextureRect(sf::IntRect({ 0, 0, (int)texture_size.x, (int)texture_size.y }));
	m_visual_body = sprite;
}

void GameObject::setOrigin(const float x, const float y)
{
	m_visual_body.setOrigin(x, y);
}


sf::Vector2f GameObject::convertPosition(const sf::Vector2f& position_vec, const sf::Vector2u& texture_size)
{
	return sf::Vector2f(float(position_vec.x * texture_size.x), float(position_vec.y * texture_size.y));
}
