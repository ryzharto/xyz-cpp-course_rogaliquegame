#include "MazeGenerator.h"
#include <algorithm>
#include <chrono>

namespace Ryzharto_RogaliqueGame
{
    MazeGenerator::MazeGenerator(int width, int height) : width(width), height(height)
    {
        // Инициализируем генератор случайных чисел текущим временем
        unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
        rng.seed(seed);

        // Сетка с запасом для стен между комнатами: размер = (2*width+1) x (2*height+1)
        int gridW = 2 * width + 1;
        int gridH = 2 * height + 1;
        grid.assign(gridW * gridH, CellType::Wall);
    }

    int MazeGenerator::GridIndex(int x, int y) const
    {
        return y * (2 * width + 1) + x;
    }

    bool MazeGenerator::IsInBounds(int x, int y) const
    {
        return (x >= 0 && x < 2 * width + 1 && y >= 0 && y < 2 * height + 1);
    }

    bool MazeGenerator::IsOuterWall(int x, int y) const
    {
        return (x == 0 || x == 2 * width || y == 0 || y == 2 * height);
    }

    bool MazeGenerator::ShouldPlaceDoor() const
    {
        std::uniform_real_distribution<float> dist(0.0f, 1.0f);
        return dist(rng) < doorProbability;
    }

    void MazeGenerator::Carve(int x, int y)
    {
        // Превращаем текущую клетку в пол
        grid[GridIndex(x, y)] = CellType::Floor;

        // Направления: вверх, вправо, вниз, влево (смещение на 2 клетки)
        const int dx[] = { 0, 2, 0, -2 };
        const int dy[] = { -2, 0, 2, 0 };

        // Перемешиваем порядок направлений
        std::vector<int> dirs = { 0, 1, 2, 3 };
        std::shuffle(dirs.begin(), dirs.end(), rng);

        for (int d : dirs)
        {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // Если соседняя клетка (через одну) в границах и ещё не является полом
            if (IsInBounds(nx, ny) && !IsOuterWall(nx, ny) && grid[GridIndex(nx, ny)] == CellType::Wall)
            {
                // Убираем стену между текущей и соседней клеткой
                int wallX = x + dx[d] / 2;
                int wallY = y + dy[d] / 2;
                if (!IsOuterWall(wallX, wallY))
                {
                    // Добавим в проем дверь по проверке
                    if (ShouldPlaceDoor())
                        grid[GridIndex(wallX, wallY)] = CellType::Door;
                    else
                        grid[GridIndex(wallX, wallY)] = CellType::Floor;
                }
                // Рекурсивно проходим в соседнюю клетку
                Carve(nx, ny);
            }
        }
    }

    void MazeGenerator::PlaceEntranceAndExit()
    {
        // Вход: левая верхняя внутренняя комната
        entrance = XYZEngine::Vector2Di{ 1, 1 };
        // Выход: правая нижняя внутренняя комната
        exit = XYZEngine::Vector2Di{ 2 * width - 1, 2 * height - 1 };

        // Помечаем их
        grid[GridIndex(entrance.x, entrance.y)] = CellType::Entrance;
        grid[GridIndex(exit.x, exit.y)] = CellType::Exit;
    }

    void MazeGenerator::Generate()
    {
        // Начинаем с внутренней клетки (1,1) – она гарантированно не внешняя стена
        Carve(1, 1);

        // Устанавливаем вход и выход
        PlaceEntranceAndExit();
    }

    CellType MazeGenerator::GetCell(int x, int y) const
    {
        if (!IsInBounds(x, y)) return CellType::Wall;
        return grid[GridIndex(x, y)];
    }

    int MazeGenerator::GetGridWidth() const
    {
        return 2 * width + 1;
    }

    int MazeGenerator::GetGridHeight() const
    {
        return 2 * height + 1;
    }

    XYZEngine::Vector2Di MazeGenerator::GetEntrance() const
    {
        return entrance;
    }

    XYZEngine::Vector2Di MazeGenerator::GetExit() const
    {
        return exit;
    }

    std::vector<XYZEngine::Vector2Di> MazeGenerator::GetFloorCells() const
    {
        std::vector<XYZEngine::Vector2Di> floors;
        for (int y = 0; y < 2 * height + 1; ++y)
        {
            for (int x = 0; x < 2 * width + 1; ++x)
            {
                CellType cell = grid[GridIndex(x, y)];
                if (cell == CellType::Floor || cell == CellType::Entrance || cell == CellType::Exit)
                    floors.push_back({ x, y });
            }
        }
        return floors;
    }
}