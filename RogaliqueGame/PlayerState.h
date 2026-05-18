#pragma once
#include <vector>
#include <string>
#include "ItemData.h"         // ItemDynamicData
#include "WeaponComponent.h"  // WeaponInfo
#include "StatsComponent.h"   // если нужно, но возьмём просто float

namespace Ryzharto_RogaliqueGame
{
    struct ItemSaveData
    {
        std::string prefabKey;
        ItemDynamicData dynamicData;
        // Действия не сохраняем, они восстановятся из прототипа
    };

    struct PlayerState
    {
        float health = 100.f;
        float armour = 0.f;
        float stamina = 100.f;
        std::vector<ItemSaveData> inventoryItems;
        std::vector<XYZEngine::WeaponInfo> weapons;   // оружие с текущими патронами
        int currentWeaponIndex = 0;                   // выбранное оружие
    };
}