#pragma once
#include <string>

namespace Ryzharto_ArcanoidGame
{
	class GameWorld
	{
	private: 
		GameWorld() = default;

	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}

		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

		const std::string GAME_NAME = "Ryzharto's Arcanoid Game";

		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEIGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		/*
		Player settings
		*/
		const float PLATFORM_WIDTH = 100.f;
		const float PLATFORM_HEIGHT = 20.f;
		const float PLATFORM_SPEED = 300.f;

		const float ACCELERATION = 10.f; // For each eaten apple snake speed will be increased by this value

		/*
		Ball settings
		*/
		const unsigned int BALL_SIZE = 20;
		const unsigned int BALL_SPEED = 400;

		/*
		Block settings
		*/
		const unsigned int BLOCK_ROWS = 4;
		const unsigned int BLOCKS_IN_ROW = 15;
		const float BLOCK_SPACING = 2.f;
		const float BREAK_DELAY = 1.f;
		const float BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_IN_ROW + 1) * BLOCK_SPACING) / BLOCKS_IN_ROW;
		const float BLOCK_HEIGHT = 30.f;

		/*
		Records table parameters
		*/
		const int MAX_RECORDS_TABLE_SIZE = 6;
		const char* PLAYER_NAME = "Player";
	};
}

#define SETTINGS GameWorld::Instance()





