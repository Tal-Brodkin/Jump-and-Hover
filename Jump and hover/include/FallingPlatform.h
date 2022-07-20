#include "DynamicObject.h"
#include "Factory.h"





class FallingPlatform : public DynamicObject
{
	bool m_fall_down = false;
	float m_elapsed_time = 0;

	static bool m_registerit;

public:

	FallingPlatform(const sf::Vector2f&, b2World*);

	void makeFall();
	virtual void update(const float) override;
};