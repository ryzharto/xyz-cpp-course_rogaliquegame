#pragma once
#include "GameObject.h"
#include "WeaponComponent.h"
#include "Item.h"
#include <string>

namespace Ryzharto_RogaliqueGame
{
    class InventoryActions
    {
    public:
        // Universal executioners
        static void ExecuteEquip(XYZEngine::GameObject* owner, const XYZEngine::WeaponInfo& info);
        static void ExecuteUnequip(XYZEngine::GameObject* owner, const XYZEngine::WeaponInfo& info);
        static void ExecuteDrop(XYZEngine::GameObject* owner, Item& item);
        static void ExecuteDestroy(XYZEngine::GameObject* owner);
    };
}