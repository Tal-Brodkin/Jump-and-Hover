#include "DynamicObject.h"
#include "Factory.h"





class MovingPlatform : public DynamicObject
{
	bool m_can_move = true;

	static bool m_registerit;

public:

	MovingPlatform(const sf::Vector2f&, b2World*);

	void canNotMove();
	bool canMove() const;

	virtual void update(const float) override;
};