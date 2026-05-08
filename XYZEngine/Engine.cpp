#include "pch.h"
#include "Engine.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "InputManager.h"
#include "UIManager.h"
#include "../RogaliqueGame/PauseMenu.h"
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

				// Handle UI events first
				UIManager::Instance()->HandleEvent(event);

				// If input is not blocked - update InputManager
				if (!UIManager::Instance()->IsInputBlocked())
					InputManager::Instance().HandleEvents(event);
			}

			// Process PauseMenu open/close
			/*if (InputManager::Instance().IsPauseButtonPressed())
			{
				if (!UIManager::Instance()->IsInputBlocked())
				{
					UIManager::Instance()->PushScreen(std::make_shared<Ryzharto_RogaliqueGame::PauseMenu>());
					LOG_INFO("ENGINE::RUN: Pause menu opened");
				}
			}*/

			// Update axes and mouse position
			InputManager::Instance().UpdateAxes();

			if (!UIManager::Instance()->IsInputBlocked())
			{
				GameWorld::Instance()->Update(deltaTime);
				GameWorld::Instance()->FixedUpdate(deltaTime);
			}
			
			// Rendering
			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}
			
			RenderSystem::Instance()->GetMainWindow().clear();
			GameWorld::Instance()->Render();
			GameWorld::Instance()->LateUpdate();
			UIManager::Instance()->Update(deltaTime);
			UIManager::Instance()->Draw(window);
			RenderSystem::Instance()->GetMainWindow().display();

			// Reset frame input flags
			InputManager::Instance().ResetFrameFlags();
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