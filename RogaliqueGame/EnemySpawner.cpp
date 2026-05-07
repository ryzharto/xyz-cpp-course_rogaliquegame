#include "EnemySpawner.h"
#include "EnemyRaptor.h"

namespace Ryzharto_RogaliqueGame
{
	std::vector<Enemy*> EnemySpawner::SpawnEnemies(const std::string& type, int count, const std::vector<XYZEngine::Vector2Df>& positions, XYZEngine::GameObject* player)
	{
		std::vector<Enemy*> enemies;
		if (positions.empty() || count <= 0) return enemies;

		if (count > positions.size())
		{
			XYZEngine::LOG_WARN("Requested " + std::to_string(count) + " enemies, but only " + std::to_string(positions.size()) + " positions available. Spawning maximum possible");
			count = positions.size();
		}

		for (int i = 0; i < count; ++i)
		{
			// Pick random position from positions vector
			//int idx = rand() % positions.size();
			Enemy* enemy = CreateEnemy(type, positions[i], player);

			if (enemy)
			{
				enemies.push_back(enemy);
				XYZEngine::LOG_INFO("Spawned enemy of type " + type + " at (" + std::to_string(positions[i].x) + ", " + std::to_string(positions[i].y) + ")");
			}
		}
		return enemies;
	}

	Enemy* EnemySpawner::CreateEnemy(const std::string& type, const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player)
	{
		if (type == "Raptor")
			return new EnemyRaptor(position, player);
		// else if (type == "PteranodonEnemy)...

		XYZEngine::LOG_WARN("Unknown enemy type: " + type);
		return nullptr;
	}
}