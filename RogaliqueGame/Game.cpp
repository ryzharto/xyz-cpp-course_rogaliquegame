#include "Game.h"
#include "DeveloperLevel.h"
#include "Player.h"
#include "StatsComponent.h"
#include "HUD.h"
#include "UIManager.h"
#include "GameWorld.h"
#include "MainMenu.h"
#include "GameOverMenu.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    Game& Game::Instance()
    {
        static Game instance;
        return instance;
    }

    void Game::Init()
    {
        // Показываем главное меню (оно само добавится в UIManager)
        UIManager::Instance()->ClearAllScreens();
        UIManager::Instance()->PushScreen(std::make_shared<MainMenu>());
        LOG_INFO("Game initialized, showing MainMenu");
    }

    void Game::Update(float deltaTime)
    {
        if (pendingNewGame)
        {
            ExecuteNewGame();
            pendingNewGame = false;
        }
        if (pendingReturnToMenu)
        {
            ExecuteReturnToMainMenu();
            pendingReturnToMenu = false;
        }
        if (pendingGameOver)
        {
            ExecuteGameOver();
            pendingGameOver = false;
        }

        // Проверяем условия победы/поражения
        if (state == State::Playing && player)
        {
            auto* stats = player->GetComponent<XYZEngine::StatsComponent>();
            if (stats && stats->GetCurrentHealth() <= 0)
            {
                RequestGameOver();
            }
        }
    }

    void Game::RequestNewGame()
    {
        if (state != State::Playing)
            pendingNewGame = true;
    }

    void Game::RequestReturnToMainMenu()
    {
        if (state == State::Playing || state == State::GameOver)
            pendingReturnToMenu = true;
    }

    void Game::RequestGameOver()
    {
        if (state == State::Playing)
            pendingGameOver = true;
    }

    void Game::ExecuteNewGame()
    {
        // Очищаем старый уровень и мир
        if (currentLevel)
        {
            currentLevel->Stop();
            currentLevel.reset();
        }
        XYZEngine::GameWorld::Instance()->Clear();
        player = nullptr;

        // Создаём новый уровень
        currentLevel = std::make_unique<DeveloperLevel>();
        currentLevel->Start();

        // Получаем игрока
        player = currentLevel->GetPlayer();
        if (player)
            XYZEngine::GameWorld::Instance()->SetPlayer(player);

        // Очищаем все экраны UI и добавляем HUD
        UIManager::Instance()->ClearAllScreens();
        if (player)
        {
            auto hud = std::make_shared<HUD>(player);
            UIManager::Instance()->PushScreen(hud);
            LOG_INFO("New game started, HUD added");
        }

        state = State::Playing;
    }

    void Game::ExecuteReturnToMainMenu()
    {
        // Останавливаем уровень и очищаем мир
        if (currentLevel)
        {
            currentLevel->Stop();
            currentLevel.reset();
        }
        XYZEngine::GameWorld::Instance()->Clear();
        player = nullptr;

        // Показываем главное меню
        UIManager::Instance()->ClearAllScreens();
        UIManager::Instance()->PushScreen(std::make_shared<MainMenu>());

        state = State::MainMenu;
        LOG_INFO("Returned to main menu");
    }
    void Game::ExecuteGameOver()
    {
        state = State::GameOver;

        UIManager::Instance()->SetScreen(std::make_shared<GameOverMenu>());
        LOG_INFO("Game Over screen displayed");
    }
}