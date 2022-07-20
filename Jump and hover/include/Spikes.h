#include "StaticObject.h"
#include "Factory.h"






class Spikes : public StaticObject
{

	static bool m_registerit;

public:

	Spikes(const sf::Vector2f&, b2World*);

	virtual void update(const float) override {};
};