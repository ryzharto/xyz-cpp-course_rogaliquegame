#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "EnemyRaptor.h"
#include "AI.h"
#include "Music.h"
#include "Floor.h"
#include "Wall.h"

using namespace XYZEngine;

namespace Ryzharto_RogaliqueGame
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;

	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<EnemyRaptor> enemy_1;
		std::shared_ptr<EnemyRaptor> enemy_2;
		std::shared_ptr<AI> ai;
		std::unique_ptr<Music> music;	
	};
}


