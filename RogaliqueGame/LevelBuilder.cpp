#include "LevelBuilder.h"
#include "PrefabCatalog.h"
#include "GameWorld.h"
#include "Vector.h"
#include "EnemySpawner.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    void LevelBuilder::Build(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        BuildFloors(world, maze);
        BuildWalls(world, maze);
        BuildEntranceAndExit(world, maze);
        PlaceDoors(world, maze);
        PopulateCrates(world,maze);
    }

    void LevelBuilder::BuildFloors(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        const float tileSize = 128.0f;
        for (int y = 0; y < maze.GetGridHeight(); ++y)
        {
            for (int x = 0; x < maze.GetGridWidth(); ++x)
            {
                CellType cell = maze.GetCell(x, y);
                if (cell == CellType::Floor || cell == CellType::Entrance || cell == CellType::Exit || cell == CellType::Door)
                {
                    XYZEngine::Vector2Df pos = { x * tileSize, y * tileSize };
                    PrefabCatalog::Instance().Instantiate("floor", pos);
                }
            }
        }
    }

    void LevelBuilder::BuildWalls(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        const float tileSize = 128.0f;
        for (int y = 0; y < maze.GetGridHeight(); ++y)
        {
            for (int x = 0; x < maze.GetGridWidth(); ++x)
            {
                if (maze.GetCell(x, y) == CellType::Wall)
                {
                    XYZEngine::Vector2Df pos = { x * tileSize, y * tileSize };
                    std::string prefabKey = GetWallPrefab(maze, x, y);
                    PrefabCatalog::Instance().Instantiate(prefabKey, pos);
                }
            }
        }
    }

    std::string LevelBuilder::GetWallPrefab(const MazeGenerator& maze, int x, int y) const
    {
        auto isFloor = [&](int nx, int ny)
            {
            CellType cell = maze.GetCell(nx, ny);
            return (cell == CellType::Floor || cell == CellType::Entrance || cell == CellType::Exit);
            };

        bool floorTop = isFloor(x, y + 1);
        bool floorBottom = isFloor(x, y - 1);
        bool floorLeft = isFloor(x - 1, y);
        bool floorRight = isFloor(x + 1, y);

        int gridW = maze.GetGridWidth() - 1;
        int gridH = maze.GetGridHeight() - 1;

        // 1. Углы
        if (x == 0 && y == 0)
            return "wall_corner_bl";    // левый‑нижний
        if (x == gridW && y == 0)
            return "wall_corner_br";    // правый‑нижний
        if (x == 0 && y == gridH)
            return "wall_corner_tl";    // левый‑верхний
        if (x == gridW && y == gridH)
            return "wall_corner_tr";    // правый‑верхний

        // 2. Границы (не углы)
        if (x == 0 && !floorRight)
            return "wall_inner_cross_open_left";    // Внешняя стена левая с перекрестком (стена справа)
        if (x == 0)                                 // левая стена
            return "wall_vertical";     

        if (x == gridW && !floorLeft)
            return "wall_inner_cross_open_right";   // Внешняя стена правая с перекрестком (стена слева)
        if (x == gridW)                             // правая стена
            return "wall_vertical";
            
        if (y == 0 && !floorTop)
            return "wall_inner_cross_open_bottom";  // Внешняя стена нижняя с перекрестком (стена сверху)
        if (y == 0)                                 // нижняя стена
            return "wall_horizontal";
        
        if (y == gridH && !floorBottom)
            return "wall_inner_cross_open_top";     // Внешняя стена верхняя с перекрестком (стена снизу)
        if (y == gridH)                             // верхняя стена
            return "wall_horizontal";

        // 3. Внутренние стены, примыкающие к полу
        if (floorTop && floorBottom && !floorLeft && !floorRight)
            return "wall_horizontal";          // горизонтальная
        if (floorLeft && floorRight && !floorTop && !floorBottom)
            return "wall_vertical";            // вертикальная

        // 4. Внутренние стены - крайние
        if (floorTop && floorBottom && !floorLeft && floorRight)
            return "wall_inner_horizontal_right";                   // Внутренняя стена крайняя правая (стена только слева)
        if (floorTop && floorBottom && floorLeft && !floorRight)    
            return "wall_inner_horizontal_left";                    // Внутренняя стена крайняя левая (стена только справа)
        if (!floorTop && floorBottom && floorLeft && floorRight)
            return "wall_inner_vertical_bottom";                    // Внутренняя стена крайняя нижняя (стена только сверху)
        if (floorTop && !floorBottom && floorLeft && floorRight)
            return "wall_inner_vertical_top";                       // Внутренняя стена крайняя верхняя (стена только снизу)

        // 5. Внутренние стены - перекрестки (стены с трех сторон)
        if (!floorTop && floorBottom && !floorLeft && !floorRight)
            return "wall_inner_cross_open_bottom";                  // Стены слева, справа, сверху
        if (floorTop && !floorBottom && !floorLeft && !floorRight)
            return "wall_inner_cross_open_top";                     // Стены слева, справа, снизу
        if (!floorTop && !floorBottom && floorLeft && !floorRight)
            return "wall_inner_cross_open_left";                    // Стены сверху, снизу, справа
        if (!floorTop && !floorBottom && !floorLeft && floorRight)
            return "wall_inner_cross_open_right";                   // Стены сверху, снизу, слева

        // 6. Внутренние стены - углы
        if (floorTop && !floorBottom && floorLeft && !floorRight)
            return "wall_inner_corner_TL";                          // Внутренний угол - верх/слева
        if (floorTop && !floorBottom && !floorLeft && floorRight)
            return "wall_inner_corner_TR";                          // Внутренний угол - верх/справа
        if (!floorTop && floorBottom && floorLeft && !floorRight)
            return "wall_inner_corner_BL";                          // Внутренний угол - низ/слева
        if (!floorTop && floorBottom && !floorLeft && floorRight)
            return "wall_inner_corner_BR";                          // Внутренний угол - низ/справа

        // 7. Всё остальное – default (можно вообще не встречаться)
        return "wall_default";
    }

    void LevelBuilder::BuildEntranceAndExit(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        const float tileSize = 128.0f;
        XYZEngine::Vector2Di entrance = maze.GetEntrance();
        XYZEngine::Vector2Di exit = maze.GetExit();

        XYZEngine::Vector2Df entrancePos = { entrance.x * tileSize, entrance.y * tileSize };
        XYZEngine::Vector2Df exitPos = { exit.x * tileSize, exit.y * tileSize };

        // Создаём интерактивные объекты входа и выхода
        PrefabCatalog::Instance().Instantiate("level_entrance", entrancePos);
        PrefabCatalog::Instance().Instantiate("level_exit", exitPos);
    }

    void LevelBuilder::PopulateEnemies(XYZEngine::GameWorld* world, const MazeGenerator& maze, XYZEngine::GameObject* player)
    {
        std::vector<XYZEngine::Vector2Di> floorCells = maze.GetFloorCells();
        // Убираем клетки слишком близко к входу и выходу
        XYZEngine::Vector2Di entrance = maze.GetEntrance();
        XYZEngine::Vector2Di exit = maze.GetExit();
        floorCells.erase(std::remove_if(floorCells.begin(), floorCells.end(),
            [&](const XYZEngine::Vector2Di& cell)
            {
                return (std::abs(cell.x - entrance.x) <= 2 && std::abs(cell.y - entrance.y) <= 2) || (std::abs(cell.x - exit.x) <= 2 && std::abs(cell.y - exit.y) <= 2);
            }), floorCells.end());

        if (floorCells.empty()) return;

        // Случайно выбираем несколько позиций для врагов (например, 3)
        std::shuffle(floorCells.begin(), floorCells.end(), std::mt19937(std::random_device()()));
        int enemyCount = std::min(3, static_cast<int>(floorCells.size()));
        std::vector<XYZEngine::Vector2Df> spawnPositions;
        for (int i = 0; i < enemyCount; ++i)
        {
            XYZEngine::Vector2Df pos = { floorCells[i].x * 128.0f, floorCells[i].y * 128.0f };
            spawnPositions.push_back(pos);
        }

        if (!spawnPositions.empty())
            EnemySpawner::SpawnEnemies("Raptor", enemyCount, spawnPositions, player);
    }

    void LevelBuilder::PopulateItems(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        std::vector<XYZEngine::Vector2Di> floorCells = maze.GetFloorCells();
        // Исключаем вход и выход
        XYZEngine::Vector2Di entrance = maze.GetEntrance();
        XYZEngine::Vector2Di exit = maze.GetExit();
        floorCells.erase(std::remove_if(floorCells.begin(), floorCells.end(),
            [&](const XYZEngine::Vector2Di& cell)
            {
                return (std::abs(cell.x - entrance.x) <= 2 && std::abs(cell.y - entrance.y) <= 2) || (std::abs(cell.x - exit.x) <= 2 && std::abs(cell.y - exit.y) <= 2);
            }), floorCells.end());

        if (floorCells.empty()) return;

        std::shuffle(floorCells.begin(), floorCells.end(), std::mt19937(std::random_device()()));

        // Разместим несколько предметов (медикаменты, патроны, винтовку)
        int itemCount = std::min(5, static_cast<int>(floorCells.size()));
        for (int i = 0; i < itemCount; ++i)
        {
            XYZEngine::Vector2Df pos = { floorCells[i].x * 128.0f, floorCells[i].y * 128.0f };
            // Случайно выбираем, что разместить
            int r = rand() % 3;
            std::string prefabKey;
            if (r == 0) prefabKey = "medkit";
            else if (r == 1) prefabKey = "ammo_box";
            else prefabKey = "rifle"; 
            PrefabCatalog::Instance().Instantiate(prefabKey, pos);
        }
    }

    void LevelBuilder::PlaceDoors(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        const float tileSize = 128.0f;
        for (int y = 0; y < maze.GetGridHeight(); ++y)
        {
            for (int x = 0; x < maze.GetGridWidth(); ++x)
            {
                CellType cell = maze.GetCell(x, y);
                if (cell == CellType::Door)
                {
                    CellType leftCell = maze.GetCell(x - 1, y);
                    CellType rightCell = maze.GetCell(x + 1, y);
                    if (leftCell == CellType::Floor || rightCell == CellType::Floor)
                    {
                        XYZEngine::Vector2Df pos = { x * tileSize, y * tileSize };
                        PrefabCatalog::Instance().Instantiate("door_locked_vertical", pos);
                    }
                    else
                    {
                        XYZEngine::Vector2Df pos = { x * tileSize, y * tileSize };
                        PrefabCatalog::Instance().Instantiate("door_locked_horizontal", pos);
                    } 
                }
            }
        }
    }

    void LevelBuilder::PopulateCrates(XYZEngine::GameWorld* world, const MazeGenerator& maze)
    {
        std::vector<XYZEngine::Vector2Di> floorCells = maze.GetFloorCells();
        XYZEngine::Vector2Di entrance = maze.GetEntrance();
        XYZEngine::Vector2Di exit = maze.GetExit();
        floorCells.erase(std::remove_if(floorCells.begin(), floorCells.end(),
            [&](const XYZEngine::Vector2Di& cell)
            {
                return (std::abs(cell.x - entrance.x) <= 2 && std::abs(cell.y - entrance.y) <= 2) ||
                    (std::abs(cell.x - exit.x) <= 2 && std::abs(cell.y - exit.y) <= 2);
            }), floorCells.end());

        if (floorCells.empty()) return;

        std::shuffle(floorCells.begin(), floorCells.end(), std::mt19937(std::random_device()()));
        int crateCount = std::min(3, static_cast<int>(floorCells.size()));
        for (int i = 0; i < crateCount; ++i)
        {
            XYZEngine::Vector2Df pos = { floorCells[i].x * 128.f, floorCells[i].y * 128.f };
            PrefabCatalog::Instance().Instantiate("crate", pos);
        }
    }
}