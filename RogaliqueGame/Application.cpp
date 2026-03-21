#include "Application.h"
#include <cstdlib>

namespace Ryzharto_ArcanoidGame
{
	Application& Application::Instance()
	{
		static Application instance;
		return instance;
	}

	Application::Application() : window(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT), SETTINGS.GAME_NAME)
	{
		// Инициализируем ГПСЧ
		unsigned int seed = (unsigned int)time(nullptr); // Задаем seed при помощи текущего времени
		srand(seed);

		//EnableConsole();
	}

	void Application::Run()
	{
		// Инициализируем счетчик времени
		sf::Clock gameClock;

		// Main loop, основной цикл
		while (window.isOpen())
		{
			// Расчет разницы во времени, отвязываем выполнение логики от скорости ПК
			float startTime = gameClock.getElapsedTime().asSeconds();

			if (!window.isOpen())
			{
				break;
			}
			game.UpdateGame(SETTINGS.TIME_PER_FRAME, window);

			float endTime = gameClock.getElapsedTime().asSeconds();
			float deltaTime = endTime - startTime;
			if (deltaTime < SETTINGS.TIME_PER_FRAME)
			{
				// Reduce framerate to not spam CPU and GPU
				sf::sleep(sf::seconds(SETTINGS.TIME_PER_FRAME - deltaTime));
			}
		}
	}
}