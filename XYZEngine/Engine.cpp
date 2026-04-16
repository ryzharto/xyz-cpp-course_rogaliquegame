#include "pch.h"
#include "Engine.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include <iostream>

namespace XYZEngine
{
	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	Engine::Engine()
	{
		// Init random number generator
		unsigned int seed = (unsigned int)time(nullptr); // Get current time as seed. You can also use any other number to fix randomization
		srand(seed);
	}

	void Engine::Run()
	{
		// Init game clock
		sf::Clock gameClock;
		sf::Event event;
		
		// Game loop
		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();

			float deltaTime = dt.asSeconds();

			while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				// Close window if close button or Escape key pressed
				if (event.type == sf::Event::Closed)
				{
					RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			RenderSystem::Instance()->GetMainWindow().clear();

			GameWorld::Instance()->Update(deltaTime);
			GameWorld::Instance()->FixedUpdate(deltaTime);
			GameWorld::Instance()->Render();
			GameWorld::Instance()->LateUpdate();

			RenderSystem::Instance()->GetMainWindow().display();
		}
	}
}