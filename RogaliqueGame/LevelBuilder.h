#pragma once
#include "MazeGenerator.h"
#include "GameObject.h"

namespace XYZEngine { class GameWorld; }

namespace Ryzharto_RogaliqueGame
{
    class LevelBuilder
    {
    public:
        void Build(XYZEngine::GameWorld* world, const MazeGenerator& maze);
        void PopulateEnemies(XYZEngine::GameWorld* world, const MazeGenerator& maze, XYZEngine::GameObject* player);
        void PopulateItems(XYZEngine::GameWorld* world, const MazeGenerator& maze);

    private:
        void BuildFloors(XYZEngine::GameWorld* world, const MazeGenerator& maze);
        void BuildWalls(XYZEngine::GameWorld* world, const MazeGenerator& maze);
        std::string GetWallPrefab(const MazeGenerator& maze, int x, int y) const;
        void BuildEntranceAndExit(XYZEngine::GameWorld* world, const MazeGenerator& maze);
        void PlaceDoors(XYZEngine::GameWorld* world, const MazeGenerator& maze);
        void PopulateCrates(XYZEngine::GameWorld* world, const MazeGenerator& maze);
    };
}