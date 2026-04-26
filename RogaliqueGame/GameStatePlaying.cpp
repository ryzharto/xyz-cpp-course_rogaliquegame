#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <cassert>
#include <sstream>
//#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "Death.wav"));
		assert(gameWinSoundBuffer.loadFromFile(SETTINGS.RESOURCES_PATH + "tada-fanfare.wav"));
		assert(backgroundTexture.loadFromFile(SETTINGS.RESOURCES_PATH + "CatsPaw_Nebula.jpg"));

		// Init Factories


		// Init background
		InitSprite(background, SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT, backgroundTexture);
		background.setPosition(SETTINGS.SCREEN_WIDTH / 2, SETTINGS.SCREEN_HEIGHT / 2);

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(48);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("TO BE CONTINUED..., ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 0.f, 0.f }));

		// Init game objects


		// Init Sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
		gameWinSound.setBuffer(gameWinSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{

	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);


		// Draw game objects


		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(SETTINGS.BLOCK_HEIGHT / 2.f, SETTINGS.SCREEN_WIDTH / 2.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1)
		{
			Game& game = Application::Instance().GetGame();
			//XYZEngine::LOG_WARN("LoadNextLevel called at final level. Triggering WinGame again?");

			game.WinGame();
		}
		else
		{
			++currentLevel;
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		
	}
}