#include "PrefabSetup.h"
#include "ResourceSystem.h"
#include "PrefabCatalog.h"
#include "InventoryActions.h"
#include "InteractionActions.h"
#include "StatsComponent.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    void SetupPrefabs()
    {
        auto& catalog = PrefabCatalog::Instance();

        // ---------- Register Handlers ----------
        catalog.RegisterHandler("Handler_HackTerminal", InteractionActions::HackTerminal);
        catalog.RegisterHandler("Handler_DestroyTerminal", InteractionActions::DestroyTerminal);
        catalog.RegisterHandler("Handler_PickUpItem", InteractionActions::PickUpItem);

        // ---------- Register Static prefabs ----------
        Prefab wallPrefab;
        wallPrefab.key = "wall_default";
        wallPrefab.name = "Wall";
        wallPrefab.textureKey = "level_walls";
        wallPrefab.textureMapIndex = 5;
        wallPrefab.textureSize = { 128, 128 };
        wallPrefab.isInteractive = false;
        wallPrefab.hasCollision = true;
        catalog.RegisterPrefab(wallPrefab.key, wallPrefab);
        InteractionActions::StorePrefab(wallPrefab.key, wallPrefab);

        Prefab ladderPrefab;
        ladderPrefab.key = "ladder";
        ladderPrefab.name = "Ladder";
        ladderPrefab.textureKey = "level_floors";
        ladderPrefab.textureMapIndex = 16;
        ladderPrefab.textureSize = { 128, 128 };
        ladderPrefab.isInteractive = false;
        ladderPrefab.hasCollision = false;
        catalog.RegisterPrefab(ladderPrefab.key, ladderPrefab);
        InteractionActions::StorePrefab(ladderPrefab.key, ladderPrefab);

        // ---------- Register interactive prefas ----------
        Prefab terminalPrefab;
        terminalPrefab.key = "terminal";
        terminalPrefab.name = "Terminal";
        terminalPrefab.textureKey = "Terminal";
        terminalPrefab.textureMapIndex = -1;
        terminalPrefab.textureSize = { 64, 64 };
        terminalPrefab.isInteractive = true;
        terminalPrefab.hasCollision = true;
        terminalPrefab.interactionRadius = 120.f;
        terminalPrefab.prompt = "Interact Terminal";
        terminalPrefab.singleUse = false;
        terminalPrefab.interactActions =
        {
            {"Hack", "Handler_HackTerminal"},
            {"Destroy", "Handler_DestroyTerminal"}
        };
        catalog.RegisterPrefab(terminalPrefab.key, terminalPrefab);
        InteractionActions::StorePrefab(terminalPrefab.key, terminalPrefab);

        Prefab medkitPrefab;
        medkitPrefab.key = "medkit";
        medkitPrefab.name = "Medkit";
        medkitPrefab.textureKey = "Medkit";
        medkitPrefab.textureMapIndex = -1;
        medkitPrefab.textureSize = { 32, 32 };
        medkitPrefab.category = ItemCategory::Consubable;
        medkitPrefab.itemActions =
        {
            {
                ItemActionType::Use, "Use", [](XYZEngine::GameObject* owner, Item*)
            {
                auto* stats = owner->GetComponent<XYZEngine::StatsComponent>();
                if (stats) stats->Heal(20.f);
            }, false
            },
            {
                ItemActionType::Drop, "Drop", [prefabKey = medkitPrefab.key](XYZEngine::GameObject* owner, Item* self)
            {
                InventoryActions::ExecuteDrop(owner, *self);
            }, false
            },
            {
                ItemActionType::Destroy, "Destroy", [](XYZEngine::GameObject* owner, Item*)
            {
                InventoryActions::ExecuteDestroy(owner);
            }, false
            }
        };
        //medkitPrefab.useEffect = [](XYZEngine::GameObject* owner) { auto* stats = owner->GetComponent<XYZEngine::StatsComponent>(); if (stats) stats->Heal(20.f); };
        medkitPrefab.isInteractive = true;
        medkitPrefab.hasCollision = false;
        medkitPrefab.interactionRadius = 50.f;
        medkitPrefab.prompt = "Pick up Medkit";
        medkitPrefab.singleUse = true;
        medkitPrefab.interactActions =
        {
            {"Pick up", "Handler_PickUpItem"}
        };
        catalog.RegisterPrefab(medkitPrefab.key, medkitPrefab);
        InteractionActions::StorePrefab(medkitPrefab.key, medkitPrefab);

        Prefab ammoBoxPrefab;
        ammoBoxPrefab.key = "ammo_box";
        ammoBoxPrefab.name = "Ammo Box";
        ammoBoxPrefab.textureKey = "Ammo_box";
        ammoBoxPrefab.textureMapIndex = -1;
        ammoBoxPrefab.textureSize = { 32, 32 };
        ammoBoxPrefab.category = ItemCategory::Consubable;
        ammoBoxPrefab.itemActions =
        {
            {
                ItemActionType::Use, "Use", [](XYZEngine::GameObject* owner, Item*)
            {
                auto* weapon = owner->GetComponent<XYZEngine::WeaponComponent>();
                if (weapon) weapon->SetMaxAmmo(weapon->GetMaxAmmo() + 10);
            }, false 
            },
            { 
                ItemActionType::Drop, "Drop", [prefabKey = ammoBoxPrefab.key](XYZEngine::GameObject* owner, Item* self)
            {
                InventoryActions::ExecuteDrop(owner, *self);
            }, false
            },
            {
                ItemActionType::Destroy, "Destroy", [](XYZEngine::GameObject* owner, Item*)
            {
                InventoryActions::ExecuteDestroy(owner);
            }, false
            }
        };
        //ammoBoxPrefab.useEffect = [](XYZEngine::GameObject* owner) { auto* weapon = owner->GetComponent<XYZEngine::WeaponComponent>(); if (weapon) weapon->SetMaxAmmo(10.f); };
        ammoBoxPrefab.isInteractive = true;
        ammoBoxPrefab.hasCollision = false;
        ammoBoxPrefab.interactionRadius = 50.f;
        ammoBoxPrefab.prompt = "Pick up Ammo";
        ammoBoxPrefab.singleUse = true;
        ammoBoxPrefab.interactActions =
        {
            {"Pick up", "Handler_PickUpItem"}
        };
        catalog.RegisterPrefab(ammoBoxPrefab.key, ammoBoxPrefab);
        InteractionActions::StorePrefab(ammoBoxPrefab.key, ammoBoxPrefab);

        Prefab riflePrefab;
        XYZEngine::WeaponInfo rifleInfo;
        rifleInfo.name = "Rifle";
        rifleInfo.icon = XYZEngine::ResourceSystem::Instance()->GetTextureShared("SMG_PPK-20");
        rifleInfo.damage = 12.f;
        rifleInfo.fireRate = 3.f;
        rifleInfo.maxAmmo = 30;
        rifleInfo.currentAmmo = 30;
        rifleInfo.reloadTime = 2.f;
        rifleInfo.bulletSpeed = 600.f;
        rifleInfo.isMelee = false;
        riflePrefab.weaponData = rifleInfo;
        riflePrefab.key = "rifle";
        riflePrefab.name = "SMG_PPK-20";
        riflePrefab.textureKey = "SMG_PPK-20";
        riflePrefab.textureMapIndex = -1;
        riflePrefab.textureSize = { 96, 32 };
        riflePrefab.category = ItemCategory::Weapon;
        riflePrefab.itemActions =
        {
            { ItemActionType::Equip, "Equip", [rifleInfo](XYZEngine::GameObject* owner, Item* self) mutable
            {
                if (self->dynamicData.currentAmmo >= 0)
                    rifleInfo.currentAmmo = self->dynamicData.currentAmmo;
                InventoryActions::ExecuteEquip(owner, rifleInfo);
            }, true
            },
            {
                ItemActionType::Unequip, "Unequip", [rifleInfo](XYZEngine::GameObject* owner, Item*)
            {
                InventoryActions::ExecuteUnequip(owner, rifleInfo);
            }, true
            },
            {
                ItemActionType::Drop, "Drop", [prefabKey = riflePrefab.key](XYZEngine::GameObject* owner, Item* self)
            {
                // Если оружие экипировано – сохраняем патроны и снимаем его
                auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                if (weaponComp && weaponComp->HasWeapon(self->GetWeaponData()->name))
                {
                    self->dynamicData.currentAmmo = weaponComp->GetCurrentAmmo(); 
                }
                InventoryActions::ExecuteDrop(owner, *self);
            }, false
            },
            {
                ItemActionType::Destroy, "Destroy", [](XYZEngine::GameObject* owner, Item* self)
            {
                auto* weaponComp = owner->GetComponent<XYZEngine::WeaponComponent>();
                if (weaponComp && self->GetWeaponData().has_value() && weaponComp->HasWeapon(self->GetWeaponData()->name))
                {
                    weaponComp->RemoveWeapon(self->GetWeaponData()->name);
                }
                InventoryActions::ExecuteDestroy(owner);
            }, false
            }
        };
        riflePrefab.isInteractive = true;
        riflePrefab.hasCollision = false;
        riflePrefab.prompt = "Pick up SMG_PPK-20";
        riflePrefab.singleUse = true;
        riflePrefab.interactActions =
        {
            {"Pick up", "Handler_PickUpItem"}
        };
        catalog.RegisterPrefab(riflePrefab.key, riflePrefab);
        InteractionActions::StorePrefab(riflePrefab.key, riflePrefab);

        XYZEngine::LOG_INFO("Prefab setup complete");
    }
}