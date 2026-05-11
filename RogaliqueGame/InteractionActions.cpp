#include "InteractionActions.h"
#include "InventoryComponent.h"
#include "Item.h"
#include "InventoryActions.h"
#include "GameWorld.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    // Определение статического члена
    std::unordered_map<std::string, Ryzharto_RogaliqueGame::Prefab> Ryzharto_RogaliqueGame::InteractionActions::s_prefabs;

    // Локальное хранилище префабов для создания Item (можно вынести в отдельный файл, но пока оставим здесь)
    void InteractionActions::StorePrefab(const std::string& key, const Ryzharto_RogaliqueGame::Prefab& prefab)
    {
        s_prefabs[key] = prefab;
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

    void InteractionActions::PickUpMedkit(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        auto* inventory = instigator->GetComponent<XYZEngine::InventoryComponent>();
        if (!inventory) return;

        auto it = s_prefabs.find("medkit");
        if (it == s_prefabs.end()) return;

        Item medkit = Item::CreateFromPrefab(it->second);
        // Добавляем лечебное действие
        medkit.actions.insert(medkit.actions.begin(), { "Use", [](XYZEngine::GameObject* owner)
            {
            InventoryActions::UseMedkit(owner);
            } });

        inventory->AddItem(medkit);
    }

    void InteractionActions::PickUpAmmoBox(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        auto* inventory = instigator->GetComponent<XYZEngine::InventoryComponent>();
        if (!inventory) return;

        auto it = s_prefabs.find("ammo_box");
        if (it == s_prefabs.end()) return;

        Item ammo = Item::CreateFromPrefab(it->second);
        ammo.actions.insert(ammo.actions.begin(), { "Use", [](XYZEngine::GameObject* owner)
            {
            InventoryActions::UseAmmoBox(owner);
            } });

        inventory->AddItem(ammo);
    }
}