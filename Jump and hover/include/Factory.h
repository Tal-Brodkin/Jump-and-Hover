#pragma once
#include <GameObject.h>
#include <memory>
#include <map>
#include <string>



template <class T>
class Factory 
{
	static auto& getMap() 
	{
		static std::map<Objects, pFnc> map;
		return map;
	}

public:

	using pFnc = std::unique_ptr<T>(*)(const sf::Vector2f&, b2World*);
	static std::unique_ptr<T> create(Objects, const sf::Vector2f&, b2World*);
	static bool registerIt(Objects name, pFnc);
};


template <class T>
std::unique_ptr<T> Factory<T>::create(Objects name, const sf::Vector2f& position, b2World* world)
{
	auto it = Factory<T>::getMap().find(name);

	if (it == Factory<T>::getMap().end())
		return nullptr;
	return it->second(position, world);
}

template <class T>
bool Factory<T>::registerIt(Objects name, pFnc f)
{
	Factory<T>::getMap().emplace(name, f);
	return true;
}