#include "StaticObject.h"
#include "Factory.h"
#include "Animation.h"
#include "GameManager.h"




class Exit : public StaticObject
{
	bool m_achieved = false;
	static bool m_registerit;

public:

	Exit(const sf::Vector2f&, b2World*);

	void achieved();
	bool isAchieved();
	virtual void update(const float) override;
};