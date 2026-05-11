#pragma once
#include "GameObject.h"
#include <string>

namespace Ryzharto_RogaliqueGame
{
    class InventoryActions
    {
    public:
        // Default item inventory actions
        static void DropItem(XYZEngine::GameObject* owner, const std::string& prefabKey);
        static void DestroyItem(XYZEngine::GameObject* owner);

        // Конкретные эффекты Use
        static void UseMedkit(XYZEngine::GameObject* owner);
        static void UseAmmoBox(XYZEngine::GameObject* owner);
    };
}