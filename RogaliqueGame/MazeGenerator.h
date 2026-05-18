#pragma once
#include "Vector.h"
#include <vector>
#include <random>

namespace Ryzharto_RogaliqueGame
{
    enum class CellType
    {
        Wall,
        Floor,
        Door,
        Entrance,
        Exit
    };

    class MazeGenerator
    {
    public:
        MazeGenerator(int width, int height);

        void Generate();

        CellType GetCell(int x, int y) const;
        int GetGridWidth() const;
        int GetGridHeight() const;
        XYZEngine::Vector2Di GetEntrance() const;
        XYZEngine::Vector2Di GetExit() const;

        // Список клеток пола, пригодных для размещения объектов
        std::vector<XYZEngine::Vector2Di> GetFloorCells() const;

    private:
        int width;    // ширина в комнатах (не в ячейках сетки)
        int height;   // высота в комнатах
        float doorProbability = 0.15f;; // Шанс появления дверей, 15%
        std::vector<CellType> grid;
        mutable std::mt19937 rng;

        XYZEngine::Vector2Di entrance;
        XYZEngine::Vector2Di exit;

        void Carve(int x, int y);
        int GridIndex(int x, int y) const;
        bool IsInBounds(int x, int y) const;
        bool IsOuterWall(int x, int y) const;
        bool ShouldPlaceDoor() const;
        void PlaceEntranceAndExit();
    };
}

