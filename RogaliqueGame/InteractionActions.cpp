#include "InteractionActions.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "Item.h"
#include "InventoryActions.h"
#include "GameWorld.h"
#include "PrefabCatalog.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    // Определение статического члена
    std::unordered_map<std::string, Ryzharto_RogaliqueGame::Prefab> Ryzharto_RogaliqueGame::InteractionActions::prefabs;

    // Локальное хранилище префабов для создания Item (можно вынести в отдельный файл, но пока оставим здесь)
    void InteractionActions::StorePrefab(const std::string& key, const Ryzharto_RogaliqueGame::Prefab& prefab)
    {
        prefabs[key] = prefab;
    }

    void InteractionActions::HackTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        XYZEngine::LOG_INFO("Terminal HACKED!");
        // Здесь может быть открытие двери и т.п.
    }

    void InteractionActions::DestroyTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        XYZEngine::GameWorld::Instance()->DestroyGameObject(self);
        XYZEngine::LOG_INFO("Terminal DESTROYED!");
    }


    void InteractionActions::PickUpItem(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        auto* inventory = instigator->GetComponent<XYZEngine::InventoryComponent>();
        if (!inventory) return;

        std::string prefabKey = self->GetName();

        const auto& catalog = PrefabCatalog::Instance();
        const Prefab* prefab = catalog.GetPrefab(prefabKey);
        if (!prefab)
        {
            XYZEngine::LOG_ERROR("PickUpItem: Prefab not found for key '" + prefabKey + "'");
        }

        Item item = Item::CreateFromPrototype(*prefab);

        if (auto* weaponOnGround = self->GetComponent<XYZEngine::WeaponComponent>())
        {
            item.dynamicData.currentAmmo = weaponOnGround->GetCurrentAmmo();
        }

        inventory->AddItem(item);

        XYZEngine::GameWorld::Instance()->DestroyGameObject(self);
    }

}