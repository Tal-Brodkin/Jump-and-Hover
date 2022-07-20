#include "CollisionHandler.h"
#include "Player.h"
#include "Spikes.h"
#include "Wall.h"
#include "Ground.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "FallingPlatform.h"
#include "BoostHover.h"
#include "Exit.h"
#include "Ground.h"



CollisionHandler& CollisionHandler::instance()
{
	static CollisionHandler handler;
	return handler;
}

namespace
{
///////////////////////////////////////////////////////////////////////////////

	void PlayerHitBoostHover(GameObject& player, GameObject& boost)
	{
		auto player_object = dynamic_cast<Player*>(&player);
		if (!player_object->isDead())
		{
			Resources::instance().playSound(TakeBoostSound);
			GameManager::instance().updateKeyStatus(UnPressed);
			player_object->resetHover();
			dynamic_cast<BoostHover*>(&boost)->deleteObject();
		}
	}

	void BoostHoverHitPlayer(GameObject& boost, GameObject& player)
	{
		PlayerHitBoostHover(player, boost);
	}

///////////////////////////////////////////////////////////////////////////////

	void PlayerHitSpikes(GameObject& player, GameObject& spikes)
	{
		auto player_object = dynamic_cast<Player*>(&player);

		if (!player_object->isDead())
			player_object->dead();

		//dynamic_cast<Player*>(&player)->on_ground(true);
	}	
	
	void SpikesHitPlayer(GameObject& spikes, GameObject& player)
	{
		PlayerHitSpikes(player, spikes);
	}

///////////////////////////////////////////////////////////////////////////////

	void PlayerHitGround(GameObject& player, GameObject& ground)
	{
		dynamic_cast<Player*>(&player)->onGround(true);
	}	
	
	void GroundHitPlayer(GameObject& ground, GameObject& player)
	{
		PlayerHitGround(player, ground);
	}

///////////////////////////////////////////////////////////////////////////////

	void PlayerHitExit(GameObject& player, GameObject& exit)
	{
		auto player_object = dynamic_cast<Player*>(&player);
		auto exit_object = dynamic_cast<Exit*>(&exit);

		if (!player_object->isDead() && !exit_object->isAchieved())
			exit_object->achieved();
	}	
	
	void ExitHitPlayer(GameObject& exit, GameObject& player)
	{
		PlayerHitExit(player, exit);
	}

///////////////////////////////////////////////////////////////////////////////

	void PlayerHitPlatform(GameObject& player, GameObject& platform)
	{
		dynamic_cast<Player*>(&player)->onGround(true);
	}	
	
	void PlatformHitPlayer(GameObject& platform, GameObject& player)
	{
		PlayerHitPlatform(player, platform);
	}

///////////////////////////////////////////////////////////////////////////////

	void PlayerHitMovingPlatform(GameObject& player, GameObject& platform)
	{
		auto platform_object = dynamic_cast<MovingPlatform*>(&platform);
		auto player_object = dynamic_cast<Player*>(&player);
		auto velocity = player_object->getLinearVelocity();

		if (platform_object->canMove() && (player_object->isHovering() || player_object->isOnGround()))
		{
			platform_object->updateLinearVelocity({ velocity.x * 1.2f, 0 });
		}
		else if (!player_object->isHovering() && velocity.y > 0)
			player_object->onGround(true);
	}	

	void MovingPlatformHitPlayer(GameObject& platform, GameObject& player)
	{
		PlayerHitMovingPlatform(player, platform);
	}

///////////////////////////////////////////////////////////////////////////////

	void MovingPlatformHitWall(GameObject& platform, GameObject& wall)
	{
		auto platform_object = dynamic_cast<MovingPlatform*>(&platform);
		platform_object->updateLinearVelocity({ 0, 0 });
		platform_object->canNotMove();
	}	
	
	void WallHitMovingPlatform(GameObject& wall, GameObject& platform)
	{
		MovingPlatformHitWall(platform, wall);
	}	
	
///////////////////////////////////////////////////////////////////////////////

	void PlayerHitFallingPlatform(GameObject& player, GameObject& platform)
	{
		dynamic_cast<Player*>(&player)->onGround(true);
		auto platform_object = dynamic_cast<FallingPlatform*>(&platform);
		platform_object->makeFall();
	}

	void FallingPlatformHitPlayer(GameObject& platform, GameObject& player)
	{
		PlayerHitFallingPlatform(player, platform);
	}

	///////////////////////////////////////////////////////////////////////////////
}


CollisionsTable CollisionHandler::initializeTable()
{
	CollisionsTable table;

	table[Key(typeid(Player), typeid(BoostHover))]		= &PlayerHitBoostHover;
	table[Key(typeid(BoostHover), typeid(Player))]		= &BoostHoverHitPlayer;

	table[Key(typeid(Player), typeid(Spikes))]			= &PlayerHitSpikes;
	table[Key(typeid(Spikes), typeid(Player))]			= &SpikesHitPlayer;

	table[Key(typeid(Player), typeid(Ground))]			= &PlayerHitGround;
	table[Key(typeid(Ground), typeid(Player))]			= &GroundHitPlayer;

	table[Key(typeid(Player), typeid(Exit))]			= &PlayerHitExit;
	table[Key(typeid(Exit), typeid(Player))]			= &ExitHitPlayer;		

	table[Key(typeid(Player), typeid(Platform))]		= &PlayerHitPlatform;
	table[Key(typeid(Platform), typeid(Player))]		= &PlatformHitPlayer;

	table[Key(typeid(Player), typeid(MovingPlatform))]  = &PlayerHitMovingPlatform;	
	table[Key(typeid(MovingPlatform), typeid(Player))]	= &MovingPlatformHitPlayer;	

	table[Key(typeid(MovingPlatform), typeid(Wall))]	= &MovingPlatformHitWall;
	table[Key(typeid(Wall), typeid(MovingPlatform))]	= &WallHitMovingPlatform;

	table[Key(typeid(Player), typeid(FallingPlatform))]	= &PlayerHitFallingPlatform;
	table[Key(typeid(FallingPlatform), typeid(Player))]	= &FallingPlatformHitPlayer;

	return table;
}


CollisionFunc CollisionHandler::search(const std::type_index& object_a, const std::type_index& object_b)
{
	static auto	table = initializeTable();

	auto table_entry = table.find(std::make_pair(object_a, object_b));

	if (table_entry == table.end())
	{
		return nullptr;
	}

	return table_entry->second;
}


void CollisionHandler::handleCollision(GameObject& object_a, GameObject& object_b)
{
	auto collision_func = search(typeid(object_a), typeid(object_b));

	if (collision_func)
		collision_func(object_a, object_b);
}