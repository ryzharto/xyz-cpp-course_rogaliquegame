#pragma once
#include "GameObject.h"
#include "Game.h"
#include "PlayerState.h"
#include <string>
#include <vector>
#include <functional>
#include <memory>

//namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
    //class Game; // forward

    using LevelFactory = std::function<void(Game* game)>;

    struct LevelInfo
    {
        std::string name;
        std::string description;
        LevelFactory factory;
    };

    class LevelManager
    {
    public:
        static LevelManager& Instance();

        void RegisterLevel(const std::string& name, const std::string& description, LevelFactory factory);
        void LoadLevel(const std::string& name);
        void LoadNextLevel();

        void SavePlayerState(XYZEngine::GameObject* player);
        void RestorePlayerState(XYZEngine::GameObject* player);

    private:
        LevelManager() = default;
        std::vector<LevelInfo> levels;
        int currentIndex = -1;
        PlayerState playerState;
    };

}