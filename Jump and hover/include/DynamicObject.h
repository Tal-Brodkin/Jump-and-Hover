#pragma once
#include "GameObject.h"





class DynamicObject : public GameObject
{

public:

	using GameObject::GameObject;
	virtual void update(const float) = 0;
};