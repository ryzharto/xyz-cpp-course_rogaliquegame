#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "EnemySpawner.h"
#include "EnemyRaptor.h"
#include "Music.h"
//#include "Floor.h"
//#include "Wall.h"

using namespace XYZEngine;

namespace Ryzharto_RogaliqueGame
{
	class DeveloperLevel : public Scene
	{
	public:
		DeveloperLevel(int width, int height) : width(width), height(height) {}
		void Start() override;
		void Restart() override;
		void Stop() override;
		XYZEngine::GameObject* const GetPlayer() { return player ? player->GetGameObject() : nullptr; };

		//std::vector<std::unique_ptr<Wall>> walls;
		//std::vector<std::unique_ptr<Floor>> floors;

	private:
		int width, height;
		std::shared_ptr<Player> player;
		std::unique_ptr<Music> music;	
	};
}


