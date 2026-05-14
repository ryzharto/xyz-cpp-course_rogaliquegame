#include "Item.h"
#include "InventoryActions.h"
#include "WeaponComponent.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    // Helper function
    static std::string ActionTypeToName(ItemActionType type)
    {
        switch (type)
        {
        case ItemActionType::Use: return "Use";
        case ItemActionType::Equip: return "Equip";
        case ItemActionType::Unequip: return "Unequip";
        case ItemActionType::Drop: return "Drop";
        case ItemActionType::Destroy: return "Destroy";
        case ItemActionType::Combine: return "Combine";
        case ItemActionType::Examine: return "Examine";
        default: return "Unknown";
        }
    }

    std::vector<ItemAction> Item::GetAvailableActions(XYZEngine::GameObject* owner) const
    {
        std::vector<ItemAction> available;
        if (!prototype || !owner) return available;

        auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();

        for (const auto& action : prototype->itemActions)
        {
            // Filter Equip/Unequip depending on having weapon
            if (action.type == ItemActionType::Equip && prototype->weaponData.has_value() && weaponComp)
            {
                if (weaponComp->HasWeapon(prototype->weaponData->name))
                    continue; // already equipped - skip "Equip" menu item
            }
            else if ((action.type == ItemActionType::Unequip && prototype->weaponData.has_value() && weaponComp))
            {
                if (!weaponComp->HasWeapon(prototype->weaponData->name))
                    continue; // not equipped - skip "Unequip"
            }
            available.push_back(action);
        }
        return available;
    }

    Item Item::CreateFromPrototype(const Prefab& prefab)
    {
        Item item;
        item.prototype = &prefab;
        return item;
    }

    /*Item Item::CreateFromPrefab(const Prefab& prefab)
    {
        Item item;
        item.name = prefab.name;
        item.prefabKey = prefab.key; // предполагаем, что ключ префаба == имя, можно уточнить
        item.iconTextureKey = prefab.textureKey; // или отдельное поле для иконки
        item.category = prefab.category;

        if (prefab.weaponData.has_value())
            item.weaponData = prefab.weaponData;

        // Generate actions according to availableActions order 
        for (auto actionType : prefab.availableActions)
        {
            switch (actionType)
            {
            case ItemActionType::Use:
                if (prefab.useEffect)
                {
                    item.actions.push_back({ ItemActionType::Use, "Use", [effect = prefab.useEffect](XYZEngine::GameObject* owner, Item*) {effect(owner);}, false });
                }
                break;

            case ItemActionType::Equip:
                if (prefab.weaponData.has_value())
                {
                    item.actions.push_back({ ItemActionType::Equip, "Equip", [info = *prefab.weaponData](XYZEngine::GameObject* owner, Item* self) mutable
                        {
                            if (self->dynamicData.currentAmmo >= 0)
                                info.currentAmmo = self->dynamicData.currentAmmo;
                            InventoryActions::ExecuteEquip(owner, info);
                        }, true });
                }
                break;

            case ItemActionType::Unequip:
                if (prefab.weaponData.has_value())
                {
                    item.actions.push_back({ ItemActionType::Unequip, "Unequip", [info = *prefab.weaponData](XYZEngine::GameObject* owner, Item*) {InventoryActions::ExecuteUnequip(owner, info);}, true });
                }
                break;

            case ItemActionType::Drop:
                item.actions.push_back({ ItemActionType::Drop, "Drop", [prefabKey = prefab.key](XYZEngine::GameObject* owner, Item* self)
                    {
                        // Если оружие экипировано – сохраняем текущие патроны и снимаем его
                        auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                        if (weaponComp && self->weaponData.has_value())
                        {
                            // Сохраняем количество патронов из WeaponComponent
                            self->dynamicData.currentAmmo = weaponComp->GetCurrentAmmo();
                            // Снимаем оружие
                            weaponComp->RemoveWeapon(self->weaponData->name);
                        }
                        InventoryActions::ExecuteDrop(owner, *self);
                    }, false });
                break;

            case ItemActionType::Destroy:
                item.actions.push_back({ ItemActionType::Destroy, "Destroy", [](XYZEngine::GameObject* owner, Item* self)
                    {
                        auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                        if (weaponComp && self->weaponData.has_value())
                        {
                            weaponComp->RemoveWeapon(self->weaponData->name);
                        }
                        InventoryActions::ExecuteDestroy(owner);
                    }, false });
                break;

            default:
                break;
            }
        }

        // Добавляем Drop и Destroy, если их ещё нет
        auto hasAction = [&](ItemActionType type) {return std::any_of(item.actions.begin(), item.actions.end(), [type](const ItemAction& a) { return a.type == type; });};

        if (!hasAction(ItemActionType::Drop))
        {
            item.actions.push_back({ ItemActionType::Drop, "Drop", [prefabKey = prefab.key](XYZEngine::GameObject* owner, Item* self)
                {
                    // Если оружие экипировано – сохраняем текущие патроны и снимаем его
                    auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                    if (weaponComp && self->weaponData.has_value())
                    {
                        // Сохраняем количество патронов из WeaponComponent
                        self->dynamicData.currentAmmo = weaponComp->GetCurrentAmmo();
                        // Снимаем оружие
                        weaponComp->RemoveWeapon(self->weaponData->name);
                    }
                    InventoryActions::ExecuteDrop(owner, *self);
                }, false });
        }

        if (!hasAction(ItemActionType::Destroy))
        {
            item.actions.push_back({ ItemActionType::Destroy, "Destroy", [](XYZEngine::GameObject* owner, Item* self)
                {
                    auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                    if (weaponComp && self->weaponData.has_value())
                    {
                        weaponComp->RemoveWeapon(self->weaponData->name);
                    }
                    InventoryActions::ExecuteDestroy(owner);
                }, false });
        }

        return item;
    }*/
}