#include "ContactListener.h"







void ContactListener::BeginContact(b2Contact* contact)
{
	auto data_a = (GameObject*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;

	auto data_b = (GameObject*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (data_a && data_b)
		CollisionHandler::instance().handleCollision(*data_a, *data_b);
}
