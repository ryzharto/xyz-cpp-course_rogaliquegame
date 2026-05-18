#include "DeveloperLevel.h"
#include "MazeGenerator.h"
#include "LevelBuilder.h"
#include "PrefabCatalog.h"
#include "Logger.h"

using namespace XYZEngine;

namespace Ryzharto_RogaliqueGame
{
	void DeveloperLevel::Start()
	{
		int width = 7;
		int height = 7;

		// MAZE GENERATOR
		MazeGenerator mazeGenerator(width, height);
		mazeGenerator.Generate();

		LevelBuilder builder;
		builder.Build(GameWorld::Instance(), mazeGenerator);

		// PLAYER
		XYZEngine::Vector2Di entrance = mazeGenerator.GetEntrance();
		XYZEngine::Vector2Df playerPos = { entrance.x * 128.f, entrance.y * 128.f };
		player = std::make_unique<Player>(playerPos);
		if (!player->GetGameObject())
		{
			LOG_ERROR("Player GameObject is null!");
		}
		LOG_INFO("Player created");

		// ENEMIES AND ITEMS
		builder.PopulateEnemies(GameWorld::Instance(), mazeGenerator, player->GetGameObject());
		builder.PopulateItems(GameWorld::Instance(), mazeGenerator);

		music = std::make_unique<Music>("music");

		XYZEngine::LOG_INFO("Maze level generated: " + std::to_string(mazeGenerator.GetGridWidth()) + "x" + std::to_string(mazeGenerator.GetGridHeight()));
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