#include "InventoryActions.h"
#include "TransformComponent.h"
#include "InventoryComponent.h"
#include "ResourceSystem.h"
#include "PrefabCatalog.h"
#include "GameWorld.h"
#include "StatsComponent.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    void InventoryActions::ExecuteEquip(XYZEngine::GameObject* owner, const XYZEngine::WeaponInfo& info)
    {
        auto* weapon = owner->GetComponent<XYZEngine::WeaponComponent>();
        if (!weapon) return;

        if (weapon->HasWeapon(info.name)) return; // already equipped

        weapon->AddWeapon(info);
        XYZEngine::LOG_INFO("Equipped weapon: " + info.name + " ammo: " + std::to_string(info.currentAmmo));
    }

    void InventoryActions::ExecuteUnequip(XYZEngine::GameObject* owner, const XYZEngine::WeaponInfo& info)
    {
        auto* weapon = owner->GetComponent<XYZEngine::WeaponComponent>();
        if (!weapon) return;

        weapon->RemoveWeapon(info.name);
        XYZEngine::LOG_INFO("Unequipped weapon: " + info.name);
    }

    void InventoryActions::ExecuteDrop(XYZEngine::GameObject* owner, Item& item)
    {
        auto* transform = owner->GetComponent<XYZEngine::TransformComponent>();
        if (!transform) return;

        // Create object from prefab
        XYZEngine::Vector2Df dropPos = transform->GetWorldPosition();
        auto* go = PrefabCatalog::Instance().Instantiate(item.GetPrefabKey(), dropPos);
        if (!go) return;
        
        // Transfer dynamic data to object
        if (item.GetCategory() == ItemCategory::Weapon && item.GetWeaponData().has_value())
        {
            auto* ownerWeaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();

            // Сохраняем патроны из экипированного оружия (если оно надето)
            if (ownerWeaponComp && ownerWeaponComp->HasWeapon(item.GetWeaponData()->name))
            {
                // Актуализируем dynamicData (лямбда Drop уже могла это сделать, но на всякий случай)
                item.dynamicData.currentAmmo = ownerWeaponComp->GetCurrentAmmo();

                // Снимаем оружие с игрока
                ownerWeaponComp->RemoveWeapon(item.GetWeaponData()->name);
            }

            // Создаём WeaponComponent на выброшенном объекте и добавляем оружие
            auto* groundWeaponComp = go->AddComponent<XYZEngine::WeaponComponent>();
            XYZEngine::WeaponInfo wi = *item.GetWeaponData();
            if (item.dynamicData.currentAmmo >= 0)
                wi.currentAmmo = item.dynamicData.currentAmmo;
            groundWeaponComp->AddWeapon(wi);
            groundWeaponComp->SetActive(false);   // чтобы не стреляло на земле
        }
        XYZEngine::LOG_INFO("Dropped item: " + item.GetName());
    }

    void InventoryActions::ExecuteDestroy(XYZEngine::GameObject* owner)
    {
        // Do nothing - just delete item from inventory
    }
}