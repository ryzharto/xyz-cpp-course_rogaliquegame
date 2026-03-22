#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "Debug.h"

namespace Ryzharto_RogaliqueGame
{
	class Application
	{
	public:
		Application(const Application& app) = delete; // delete copy operator
		Application& operator= (const Application&) = delete; // delete == operator 

		static Application& Instance();

		void Run();

		Game& GetGame() { return game; }

	private:
		Application(); // constructor
		~Application() = default; // destructor

	private:
		Game game;
		sf::RenderWindow window;
	};
}