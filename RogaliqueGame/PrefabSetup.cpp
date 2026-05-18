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

        /* Walls */
        Prefab wallPrefab;
        wallPrefab.key = "wall_default";
        wallPrefab.name = "Wall";
        wallPrefab.textureKey = "level_walls";
        wallPrefab.textureMapIndex = 5;
        wallPrefab.textureSize = { 128, 128 };
        wallPrefab.isInteractive = false;
        wallPrefab.hasCollision = true;
        catalog.RegisterPrefab(wallPrefab.key, wallPrefab);

        Prefab wallCornerTL = wallPrefab;
        wallCornerTL.key = "wall_corner_tl";
        wallCornerTL.textureMapIndex = 1;
        catalog.RegisterPrefab(wallCornerTL.key, wallCornerTL);

        Prefab wallCornerTR = wallPrefab;
        wallCornerTR.key = "wall_corner_tr";
        wallCornerTR.textureMapIndex = 3;
        catalog.RegisterPrefab(wallCornerTR.key, wallCornerTR);

        Prefab wallCornerBL = wallPrefab;
        wallCornerBL.key = "wall_corner_bl";
        wallCornerBL.textureMapIndex = 25;
        catalog.RegisterPrefab(wallCornerBL.key, wallCornerBL);

        Prefab wallCornerBR = wallPrefab;
        wallCornerBR.key = "wall_corner_br";
        wallCornerBR.textureMapIndex = 27;
        catalog.RegisterPrefab(wallCornerBR.key, wallCornerBR);

        Prefab wallInnerCornerTL = wallPrefab;
        wallInnerCornerTL.key = "wall_inner_corner_TL";
        wallInnerCornerTL.textureMapIndex = 1;
        catalog.RegisterPrefab(wallInnerCornerTL.key, wallInnerCornerTL);

        Prefab wallInnerCornerTR = wallPrefab;
        wallInnerCornerTR.key = "wall_inner_corner_TR";
        wallInnerCornerTR.textureMapIndex = 3;
        catalog.RegisterPrefab(wallInnerCornerTR.key, wallInnerCornerTR);

        Prefab wallInnerCornerBL = wallPrefab;
        wallInnerCornerBL.key = "wall_inner_corner_BL";
        wallInnerCornerBL.textureMapIndex = 25;
        catalog.RegisterPrefab(wallInnerCornerBL.key, wallInnerCornerBL);

        Prefab wallInnerCornerBR = wallPrefab;
        wallInnerCornerBR.key = "wall_inner_corner_BR";
        wallInnerCornerBR.textureMapIndex = 27;
        catalog.RegisterPrefab(wallInnerCornerBR.key, wallInnerCornerBR);

        Prefab wallVertical = wallPrefab;
        wallVertical.key = "wall_vertical";
        wallVertical.textureMapIndex = 12;
        catalog.RegisterPrefab(wallVertical.key, wallVertical);

        Prefab wallHorizontal = wallPrefab;
        wallHorizontal.key = "wall_horizontal";
        wallHorizontal.textureMapIndex = 38;
        catalog.RegisterPrefab(wallHorizontal.key, wallHorizontal);

        Prefab wallInnerHR = wallPrefab;
        wallInnerHR.key = "wall_inner_horizontal_right";
        wallInnerHR.textureMapIndex = 39;
        catalog.RegisterPrefab(wallInnerHR.key, wallInnerHR);

        Prefab wallInnerHL = wallPrefab;
        wallInnerHL.key = "wall_inner_horizontal_left";
        wallInnerHL.textureMapIndex = 37;
        catalog.RegisterPrefab(wallInnerHL.key, wallInnerHL);

        Prefab wallInnerVB = wallPrefab;
        wallInnerVB.key = "wall_inner_vertical_bottom";
        wallInnerVB.textureMapIndex = 24;
        catalog.RegisterPrefab(wallInnerVB.key, wallInnerVB);

        Prefab wallInnerVT = wallPrefab;
        wallInnerVT.key = "wall_inner_vertical_top";
        wallInnerVT.textureMapIndex = 0;
        catalog.RegisterPrefab(wallInnerVT.key, wallInnerVT);

        Prefab wallInnerCrossOB = wallPrefab;
        wallInnerCrossOB.key = "wall_inner_cross_open_bottom";
        wallInnerCrossOB.textureMapIndex = 26;
        catalog.RegisterPrefab(wallInnerCrossOB.key, wallInnerCrossOB);

        Prefab wallInnerCrossOT = wallPrefab;
        wallInnerCrossOT.key = "wall_inner_cross_open_top";
        wallInnerCrossOT.textureMapIndex = 2;
        catalog.RegisterPrefab(wallInnerCrossOT.key, wallInnerCrossOT);

        Prefab wallInnerCrossOL = wallPrefab;
        wallInnerCrossOL.key = "wall_inner_cross_open_left";
        wallInnerCrossOL.textureMapIndex = 13;
        catalog.RegisterPrefab(wallInnerCrossOL.key, wallInnerCrossOL);

        Prefab wallInnerCrossOR = wallPrefab;
        wallInnerCrossOR.key = "wall_inner_cross_open_right";
        wallInnerCrossOR.textureMapIndex = 15;
        catalog.RegisterPrefab(wallInnerCrossOR.key, wallInnerCrossOR);

        /* Floors */
        Prefab floorPrefab;
        floorPrefab.key = "floor";
        floorPrefab.name = "floor";
        floorPrefab.textureKey = "level_floors";
        floorPrefab.textureMapIndex = 0;
        floorPrefab.textureSize = { 128, 128 };
        floorPrefab.isInteractive = false;
        floorPrefab.hasCollision = false;
        catalog.RegisterPrefab(floorPrefab.key, floorPrefab);

        /* Ladder */
        Prefab ladderPrefab = floorPrefab;
        ladderPrefab.key = "ladder";
        ladderPrefab.name = "Ladder";
        ladderPrefab.textureMapIndex = 35;
        catalog.RegisterPrefab(ladderPrefab.key, ladderPrefab);

        Prefab entrancePrefab = floorPrefab;   // наследуем от пола, но с другим индексом
        entrancePrefab.key = "level_entrance";
        entrancePrefab.textureMapIndex = 34;   // лестница вниз
        entrancePrefab.isInteractive = false;  // вход не интерактивный, игрок просто стартует здесь
        catalog.RegisterPrefab(entrancePrefab.key, entrancePrefab);

        // ---------- Register interactive prefas ----------

        /* Terminal */
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

        /* Medkit */
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

        /* AmmoBox */
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

        /* Rifle */
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

        /* Door (closed) */
        Prefab doorPrefab;
        doorPrefab.key = "door_locked";
        doorPrefab.name = "Door";
        doorPrefab.textureKey = "Door_Locked";
        doorPrefab.textureMapIndex = -1;
        doorPrefab.textureSize = { 128, 128 };
        doorPrefab.isInteractive = true;
        doorPrefab.hasCollision = true;
        doorPrefab.interactionRadius = 200.f;
        doorPrefab.prompt = "Press E: Unlock Door";
        doorPrefab.singleUse = true;
        doorPrefab.interactActions =
        {
            {"Unlock", "Handler_UnlockDoor"}
        };
        catalog.RegisterPrefab(doorPrefab.key, doorPrefab);
        InteractionActions::StorePrefab(doorPrefab.key, doorPrefab);
        catalog.RegisterHandler("Handler_UnlockDoor", InteractionActions::UnlockDoor);

        Prefab doorHorizontalPrefab;
        doorHorizontalPrefab.key = "door_locked_horizontal";
        doorHorizontalPrefab.name = "Door";
        doorHorizontalPrefab.textureKey = "level_floors";
        doorHorizontalPrefab.textureMapIndex = 41;
        doorHorizontalPrefab.textureSize = { 128, 128 };
        doorHorizontalPrefab.isInteractive = true;
        doorHorizontalPrefab.hasCollision = true;
        doorHorizontalPrefab.interactionRadius = 200.f;
        doorHorizontalPrefab.prompt = "Press E: Unlock Door";
        doorHorizontalPrefab.singleUse = true;
        doorHorizontalPrefab.interactActions =
        {
            {"Unlock", "Handler_UnlockDoor"}
        };
        catalog.RegisterPrefab(doorHorizontalPrefab.key, doorHorizontalPrefab);
        InteractionActions::StorePrefab(doorHorizontalPrefab.key, doorHorizontalPrefab);
        catalog.RegisterHandler("Handler_UnlockDoor", InteractionActions::UnlockDoor);

        Prefab doorVerticalPrefab;
        doorVerticalPrefab.key = "door_locked_vertical";
        doorVerticalPrefab.name = "Door";
        doorVerticalPrefab.textureKey = "level_floors";
        doorVerticalPrefab.textureMapIndex = 48;
        doorVerticalPrefab.textureSize = { 128, 128 };
        doorVerticalPrefab.isInteractive = true;
        doorVerticalPrefab.hasCollision = true;
        doorVerticalPrefab.interactionRadius = 200.f;
        doorVerticalPrefab.prompt = "Press E: Unlock Door";
        doorVerticalPrefab.singleUse = true;
        doorVerticalPrefab.interactActions =
        {
            {"Unlock", "Handler_UnlockDoor"}
        };
        catalog.RegisterPrefab(doorVerticalPrefab.key, doorVerticalPrefab);
        InteractionActions::StorePrefab(doorVerticalPrefab.key, doorVerticalPrefab);
        catalog.RegisterHandler("Handler_UnlockDoor", InteractionActions::UnlockDoor);

        /* Crate */
        Prefab cratePrefab;
        cratePrefab.key = "crate";
        cratePrefab.name = "Crate";
        cratePrefab.textureKey = "level_floors";
        cratePrefab.textureMapIndex = 45;
        cratePrefab.textureSize = { 128, 128 };
        cratePrefab.isInteractive = true;
        cratePrefab.hasCollision = true;
        cratePrefab.interactionRadius = 200.f;
        cratePrefab.prompt = "Press E: Break Crate";
        cratePrefab.singleUse = true;
        cratePrefab.interactActions =
        {
            {"Break", "Handler_BreakCrate"}
        };
        catalog.RegisterPrefab(cratePrefab.key, cratePrefab);
        InteractionActions::StorePrefab(cratePrefab.key, cratePrefab);
        catalog.RegisterHandler("Handler_BreakCrate", InteractionActions::BreakCrate);

        /* Computer */
        Prefab computerPrefab;
        computerPrefab.key = "computer";
        computerPrefab.name = "Computer";
        computerPrefab.textureKey = "Terminal";   // используем уже загруженную текстуру терминала
        computerPrefab.textureMapIndex = -1;
        computerPrefab.textureSize = { 64, 64 };
        computerPrefab.isInteractive = true;
        computerPrefab.hasCollision = true;
        computerPrefab.interactionRadius = 120.f;
        computerPrefab.prompt = "Press E: Activate Computer";
        computerPrefab.singleUse = false;   // можно использовать многократно
        computerPrefab.interactActions =
        {
            {"Activate", "Handler_ActivateComputer"}
        };
        catalog.RegisterPrefab(computerPrefab.key, computerPrefab);
        InteractionActions::StorePrefab(computerPrefab.key, computerPrefab);
        catalog.RegisterHandler("Handler_ActivateComputer", InteractionActions::ActivateComputer);

        /* Level Exit */
        Prefab levelExitPrefab;
        levelExitPrefab.key = "level_exit";
        levelExitPrefab.name = "Exit";
        levelExitPrefab.textureKey = "level_floors";   // временно, позже специальная текстура
        levelExitPrefab.textureMapIndex = 35;          // другой тайл
        levelExitPrefab.textureSize = { 128, 128 };
        levelExitPrefab.isInteractive = true;
        levelExitPrefab.hasCollision = false;
        levelExitPrefab.interactionRadius = 200.f;
        levelExitPrefab.prompt = "Press E: Exit Level";
        levelExitPrefab.singleUse = false;
        levelExitPrefab.interactActions =
        {
            {"Use", "Handler_UseLevelExit"}
        };
        catalog.RegisterPrefab(levelExitPrefab.key, levelExitPrefab);
        InteractionActions::StorePrefab(levelExitPrefab.key, levelExitPrefab);
        catalog.RegisterHandler("Handler_UseLevelExit", InteractionActions::UseLevelExit);

        /* End of prefabs */
        XYZEngine::LOG_INFO("Prefab setup complete");
    }
}