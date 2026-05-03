#include "pch.h"
#include "Engine.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include <iostream>
#include <cassert>

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

		SetupLogger();
	}

	void Engine::Run()
	{
		sf::RenderWindow& window = RenderSystem::Instance()->GetMainWindow();
		if (!window.isOpen())
		{
			LOG_ERROR("Main window is not open. Engine cannot run.");
			assert(false);  // в debug остановимся здесь
			throw std::runtime_error("Main window not open");
		}

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

	void Engine::SetupLogger()
	{
		auto logger = std::make_shared<Logger>();
		logger->addSink(std::make_shared<ConsoleSink>());
		logger->addSink(std::make_shared<FileSink>("log.txt"));

		LoggerRegistry::getInstance().registerLogger("global", logger);
		LoggerRegistry::getInstance().setDefaultLogger(logger);
		LOG_INFO("Logger initialized with ConsoleSink and FileSink (log.txt)");
	}
}