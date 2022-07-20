#pragma once
#include "GameObject.h"





class StaticObject : public GameObject
{

	bool m_delete = false;

public:

	using GameObject::GameObject;

	bool isToDelete() const;

	void deleteObject();

	virtual void update(const float) = 0;
};