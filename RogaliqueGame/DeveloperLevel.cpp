#include "DeveloperLevel.h"
#include "MazeGenerator.h"
#include "PrefabCatalog.h"
#include "Logger.h"

// TEST INDLUDES
#include "InteractableComponent.h"

using namespace XYZEngine;

namespace Ryzharto_RogaliqueGame
{
	void DeveloperLevel::Start()
	{
		int width = 15;
		int height = 15;

		for (int y = 0; y < height + 1; y++)
		{
			for (int x = 0; x < width + 1; x++)
			{
				//if not wall place
				if (x != 0 && x != width && y != 0 && y != height)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(0)));
				}

				//if left-bottom corner
				if (x == 0 && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(25)));
				}

				//if right-bottom corner
				if (x == width && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(27)));
				}

				//if left-top corner
				if (x == 0 && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(1)));
				}

				//if right-top corner
				if (x == width && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(3)));
				}

				//if left (not corner)
				if (x == 0 && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(18)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
				}

				//if right (not corner)
				if (x == width && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(19)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
				}

				//if bottom (not corner)
				if (y == 0 && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
				}

				//if top (not corner)
				if (y == height && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
				}
			}
		}

		// MAZE GENERATOR
		MazeGenerator mazeGenerator(width, height, this);
		//mazeGenerator.Generate();

		LOG_INFO("Level generation: " + std::to_string(floors.size()) + " floors, " + std::to_string(walls.size()) + " walls created.");

		// PLAYER
		player = std::make_unique<Player>(std::forward<XYZEngine::Vector2Df>({width / 2 * 128.f, height / 2 * 128.f}));
		if (!player->GetGameObject())
		{
			LOG_ERROR("Player GameObject is null!");
		}
		LOG_INFO("Player created");

		// ENEMIES
		// EnemySpawner
		std::vector<XYZEngine::Vector2Df> spawnPositions = {	{ width / 2.f * 128.f, height / 4.f * 128.f }, 
																{ width / 3.f * 128.f, height / 2.f * 128.f }, 
																{ width / 3.f * 128.f, height / 3.f * 128.f } };

		auto enemies = EnemySpawner::SpawnEnemies("Raptor", 3, spawnPositions, player->GetGameObject());

		// TEST OBJECTS
		auto& catalog = Ryzharto_RogaliqueGame::PrefabCatalog::Instance();
		catalog.Instantiate("wall_default", { 100.f, 200.f });
		catalog.Instantiate("ladder", { 100.f, 100.f });
		catalog.Instantiate("terminal", { 300.f, 400.f });
		catalog.Instantiate("ammo_box", { 400.f, 400.f });
		catalog.Instantiate("medkit", { 500.f, 400.f });
		catalog.Instantiate("rifle", { 600.f, 400.f });

		music = std::make_unique<Music>("music");
	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		GameWorld::Instance()->Clear();
	}
}