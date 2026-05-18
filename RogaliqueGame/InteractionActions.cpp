#include "InteractionActions.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "Item.h"
#include "InventoryActions.h"
#include "GameWorld.h"
#include "PrefabCatalog.h"
#include "LevelManager.h"
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

    void InteractionActions::UnlockDoor(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        // Simple realization - door changed to floor
        XYZEngine::GameWorld* world = XYZEngine::GameWorld::Instance();
        XYZEngine::Vector2Df pos = self->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition();
        world->DestroyGameObject(self); // delete door
        //PrefabCatalog::Instance().Instantiate("floor", pos); // change to floor
        XYZEngine::LOG_INFO("Door unlocked and replaced with floor");
        XYZEngine::LOG_INFO("Door unlocked");
    }

    void InteractionActions::BreakCrate(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        // Create random object next to crate (medkit ar ammobox)
        XYZEngine::Vector2Df pos = self->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition();
        XYZEngine::GameWorld::Instance()->DestroyGameObject(self);
        // Random object
        std::string prefabKey = (rand() % 2 == 0) ? "medkit" : "ammo_box";
        PrefabCatalog::Instance().Instantiate(prefabKey, pos);
        XYZEngine::LOG_INFO("Crate broken, spawned " + prefabKey);
    }

    void InteractionActions::ActivateComputer(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        XYZEngine::LOG_INFO("Computer activated! (no effect yet)");
        // В будущем: открыть удалённую дверь, опустить мост и т.д.
    }

    void InteractionActions::UseLevelExit(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        LevelManager::Instance().LoadNextLevel();
        XYZEngine::LOG_INFO("Level exit used. Loading next level...");
        // Пока заглушка, позже вызовет LevelManager::Instance().LoadNextLevel();
    }


}