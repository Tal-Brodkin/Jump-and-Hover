#include "GameObject.h"
#include <typeindex>
#include <typeinfo>



using CollisionFunc = void (*)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
using CollisionsTable = std::map<Key, CollisionFunc>;



class CollisionHandler
{
	CollisionHandler() = default;
	CollisionsTable initializeTable();
	CollisionFunc search(const std::type_index&, const std::type_index&);

public:

	static CollisionHandler& instance();
	void handleCollision(GameObject&, GameObject&);
};