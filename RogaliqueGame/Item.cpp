#include "Item.h"
#include "Prefab.h"
#include "InventoryActions.h"

namespace Ryzharto_RogaliqueGame
{
    Item Item::CreateFromPrefab(const Prefab& prefab)
    {
        Item item;
        item.name = prefab.name;
        item.prefabKey = prefab.key; // предполагаем, что ключ префаба == имя, можно уточнить
        item.iconTextureKey = prefab.textureKey; // или отдельное поле для иконки

        // Standard inventory screen actions
        // Drop
        item.actions.push_back({
            "Drop",
            [prefabKey = item.prefabKey](XYZEngine::GameObject* owner)
            {
                InventoryActions::DropItem(owner, prefabKey);
            }
            });

        // Destroy
        item.actions.push_back({
            "Destroy",
            [](XYZEngine::GameObject* owner)
            {
                InventoryActions::DestroyItem(owner);
            }
            });

        return item;
    }
}