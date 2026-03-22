#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameStateData.h"
#include "LevelLoader.h"
#include "IObserver.h"

#include <unordered_map>

namespace Ryzharto_RogaliqueGame
{
	class Game;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

		int score = 0;

	private:

		// Resources
		sf::Font font;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;
		sf::SoundBuffer bonusSoundBuffer;

		// Game data


		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::Sprite background;
		sf::Texture backgroundTexture;

		// Sounds
		sf::Sound gameOverSound;
		sf::Sound gameWinSound;
		sf::Sound bonusSound;

		// Blocks creator
		int breakableBlocksCount = 0;

		// Levels
		LevelLoader levelLoader;
		int currentLevel = 0;
	};
}