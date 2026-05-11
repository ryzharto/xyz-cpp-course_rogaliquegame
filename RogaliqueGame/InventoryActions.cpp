#include "InventoryActions.h"
#include "TransformComponent.h"
#include "PrefabCatalog.h"
#include "GameWorld.h"
#include "StatsComponent.h"
#include "WeaponComponent.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    void InventoryActions::DropItem(XYZEngine::GameObject* owner, const std::string& prefabKey)
    {
        auto* transform = owner->GetComponent<XYZEngine::TransformComponent>();
        if (!transform) return;

        XYZEngine::Vector2Df dropPos = transform->GetWorldPosition();
        // Create object from prefab
        PrefabCatalog::Instance().Instantiate(prefabKey, dropPos);
        // Сам предмет будет удалён из инвентаря в InventoryComponent::UseItem после выполнения действия
    }

    void InventoryActions::DestroyItem(XYZEngine::GameObject* owner)
    {
        // Ничего не делаем – предмет просто будет удалён.
    }

    void InventoryActions::UseMedkit(XYZEngine::GameObject* owner)
    {
        auto* stats = owner->GetComponent<XYZEngine::StatsComponent>();
        if (stats) stats->Heal(20.f);
    }

    void InventoryActions::UseAmmoBox(XYZEngine::GameObject* owner)
    {
        auto* weapon = owner->GetComponent<XYZEngine::WeaponComponent>();
        if (weapon) {
            weapon->SetMaxAmmo(weapon->GetMaxAmmo() + 10);
            XYZEngine::LOG_INFO("Ammo box used, total ammo: " + std::to_string(weapon->GetCurrentAmmo()));
        }
    }
}