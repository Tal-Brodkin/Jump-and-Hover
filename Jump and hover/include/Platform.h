#include "StaticObject.h"
#include "Factory.h"





class Platform : public StaticObject
{

	static bool m_registerit;

public:

	Platform(const sf::Vector2f&, b2World*);

	virtual void update(const float) override {};
};