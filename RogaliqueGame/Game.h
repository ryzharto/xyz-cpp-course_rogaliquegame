#pragma once
#include <memory>
#include "GameObject.h"

namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
    class DeveloperLevel;
    class HUD;

    class Game
    {
    public:
        static Game& Instance();

        void Init();                     // вызывается из main после загрузки ресурсов
        void Update(float deltaTime);    // вызывается каждый кадр в Engine::Run

        void RequestNewGame();           // запланировать переход к новой игре
        void RequestReturnToMainMenu();  // запланировать выход в главное меню
        void RequestGameOver();

        bool IsPlaying() const { return state == State::Playing; }
        XYZEngine::GameObject* GetPlayer() const { return player; }

    private:
        Game() = default;

        enum class State { MainMenu, Playing, GameOver };
        State state = State::MainMenu;

        std::unique_ptr<DeveloperLevel> currentLevel;
        XYZEngine::GameObject* player = nullptr;

        // Флаги отложенных переходов
        bool pendingNewGame = false;
        bool pendingReturnToMenu = false;
        bool pendingGameOver = false;

        void ExecuteNewGame();
        void ExecuteReturnToMainMenu();
        void ExecuteGameOver();
    };
}