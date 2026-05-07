#pragma once
#include <vector>
#include <string>
#include "Vector.h"
#include "GameObject.h"
#include "Enemy.h"

namespace Ryzharto_RogaliqueGame
{
	// Spawns count of enemies of type in random positions from positions
	class EnemySpawner
	{
	public:
		// Returns created GameObjects (or Enemy fasades)
		static std::vector<Enemy*> SpawnEnemies(const std::string& type, int count, const std::vector<XYZEngine::Vector2Df>& positions, XYZEngine::GameObject* player);

	private:
		// Fabric by Type
		static Enemy* CreateEnemy(const std::string& type, const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player);
	};
}


