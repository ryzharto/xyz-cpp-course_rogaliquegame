#include "Game.h"
#include <assert.h>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"

namespace Ryzharto_RogaliqueGame
{
	Game::Game()
	{
		maxBlocks = SETTINGS.BLOCK_ROWS * SETTINGS.BLOCKS_IN_ROW;
		// Generate fake records table
		recordsTable =
		{
			{"Nina", maxBlocks - 1},
			{"Shurik", maxBlocks / 2 },
			{"Tov_Saakhov", maxBlocks / 3 },
			{"Byvaliy", maxBlocks / 4 },
			{"Balbes", maxBlocks / 5 },
			{"Trus", maxBlocks / 6 },
		};

		StateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	/* Обработка событий */
	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event; // Обработка событий от OS
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (StateStack.size() > 0)
			{
				StateStack.back().HandleWindowEvent(event);
			}
		}
	}

	/* Функция обновления состояния Playing */
	bool Game::Update(float deltaTime)
	{
		if (StateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (StateStack.size() > 0)
			{
				StateStack.pop_back();
			}
		}
		else if (StateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (StateStack.size() > 0)
			{
				StateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			StateStack.push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		StateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (StateStack.size() > 0)
		{
			StateStack.back().Update(deltaTime);
			return true;
		}

		return false;
	}

	// Отрисовать обновленные данные 
	void Game::Draw(sf::RenderWindow& window)
	{
		if (StateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = StateStack.rbegin(); it != StateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (StateStack.size() > 0)
		{
			StateStack.pop_back();
		}

		StateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		StateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		StateChangeType = GameStateChangeType::Pop;
	}

	void Game::ExitGame()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		StateChangeType = GameStateChangeType::Switch;
	}

	void Game::ShowRecords()
	{
		PushState(GameStateType::Records, true);
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value)
		{
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else
		{
			option = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}

	int Game::GetRecordByPlayerId(const std::string& playerId) const
	{
		auto it = recordsTable.find(playerId);
		return it == recordsTable.end() ? 0 : it->second;
	}

	void Game::QuitGame()
	{
		SwitchStateTo(GameStateType::None);
	}

	void Game::UpdateRecord(const std::string& playerId, int score)
	{
		recordsTable[playerId] = std::max(recordsTable[playerId], score);
	}

	void Game::StartGame()
	{
		SwitchStateTo(GameStateType::Playing);
	}

	void Game::PauseGame()
	{
		PushState(GameStateType::ExitDialog, false);
	}

	void Game::WinGame()
	{
		PushState(GameStateType::GameWin, false);
	}

	void Game::LooseGame()
	{
		PushState(GameStateType::GameOver, false);
	}

	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		HandleWindowEvents(window);
		if (Update(timeDelta))
		{
			// Draw everything here
			// Clear the window first
			window.clear();

			Draw(window);

			// End the current frame, display window contents on screen
			window.display();
		}
		else
		{
			window.close();
		}
	}

	void Game::LoadNextLevel()
	{
		assert(StateStack.back().GetType() == GameStateType::Playing);
		auto playingData = (StateStack.back().GetData<GameStatePlayingData>());
		playingData->LoadNextLevel();
	}
}

