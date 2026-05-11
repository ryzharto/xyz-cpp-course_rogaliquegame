#include "PrefabSetup.h"
#include "PrefabCatalog.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "StatsComponent.h"
#include "GameWorld.h"
#include "Logger.h"

// ---------- Handlers (free functions) ----------
namespace
{
    void Handler_HackTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        XYZEngine::LOG_INFO("Terminal HACKED!");
        // здесь может быть открытие двери, включение моста и т.п.
    }

    void Handler_DestroyTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        XYZEngine::GameWorld::Instance()->DestroyGameObject(self);
        XYZEngine::LOG_INFO("Terminal DESTROYED!");
    }

    void Handler_AddMedkit(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        auto* inventory = instigator->GetComponent<XYZEngine::InventoryComponent>();
        if (inventory)
        {
            Ryzharto_RogaliqueGame::Item medkit("Medkit", "Restores 20 HP",
                {
                Ryzharto_RogaliqueGame::ItemAction{"Use", [](XYZEngine::GameObject* owner)
                {
                    auto* stats = owner->GetComponent<XYZEngine::StatsComponent>();
                    if (stats) stats->Heal(20.f);
                }}
                });
            inventory->AddItem(medkit);
        }
    }

    void Handler_AddAmmoBox(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
    {
        auto* weapon = instigator->GetComponent<XYZEngine::WeaponComponent>();
        if (weapon)
        {
            // ƒобавл€ем 10 патронов
            weapon->SetMaxAmmo(weapon->GetMaxAmmo() + 10);
            XYZEngine::LOG_INFO("Ammo box picked up, ammo: " + std::to_string(weapon->GetCurrentAmmo()));
        }
    }
}

namespace Ryzharto_RogaliqueGame
{
    void SetupPrefabs()
    {
        auto& catalog = PrefabCatalog::Instance();

        // ---------- Register Handlers ----------
        catalog.RegisterHandler("Handler_HackTerminal", Handler_HackTerminal);
        catalog.RegisterHandler("Handler_DestroyTerminal", Handler_DestroyTerminal);
        catalog.RegisterHandler("Handler_AddMedkit", Handler_AddMedkit);
        catalog.RegisterHandler("Handler_AddAmmoBox", Handler_AddAmmoBox);

        // ---------- Register Static prefabs ----------
        Prefab wallPrefab;
        wallPrefab.name = "Wall";
        wallPrefab.textureKey = "level_walls";
        wallPrefab.textureMapIndex = 5;
        wallPrefab.textureSize = { 128, 128 };
        wallPrefab.isInteractive = false;
        wallPrefab.hasCollision = true;
        catalog.RegisterPrefab("wall_default", wallPrefab);

        Prefab ladderPrefab;
        ladderPrefab.name = "Ladder";
        ladderPrefab.textureKey = "level_floors";
        ladderPrefab.textureMapIndex = 16;
        ladderPrefab.textureSize = { 128, 128 };
        ladderPrefab.isInteractive = false;
        ladderPrefab.hasCollision = false;
        catalog.RegisterPrefab("ladder", ladderPrefab);

        // ---------- Register interactive prefas ----------
        Prefab terminalPrefab;
        terminalPrefab.name = "Terminal";
        terminalPrefab.textureKey = "Terminal";
        terminalPrefab.textureMapIndex = -1;
        terminalPrefab.textureSize = { 64, 64 };
        terminalPrefab.isInteractive = true;
        terminalPrefab.hasCollision = true;
        terminalPrefab.interactionRadius = 120.f;
        terminalPrefab.prompt = "Press E: Terminal";
        terminalPrefab.singleUse = false;
        terminalPrefab.actions =
        {
            {"Hack", "Handler_HackTerminal"},
            {"Destroy", "Handler_DestroyTerminal"}
        };
        catalog.RegisterPrefab("terminal", terminalPrefab);

        Prefab medkitPrefab;
        medkitPrefab.name = "Medkit";
        medkitPrefab.textureKey = "Medkit";
        terminalPrefab.textureMapIndex = -1;
        medkitPrefab.textureSize = { 32, 32 };
        medkitPrefab.isInteractive = true;
        medkitPrefab.hasCollision = false;
        medkitPrefab.prompt = "Press E: Pick up Medkit";
        medkitPrefab.singleUse = true;
        medkitPrefab.actions =
        {
            {"Pick up", "Handler_AddMedkit"}
        };
        catalog.RegisterPrefab("medkit", medkitPrefab);

        Prefab ammoBoxPrefab;
        ammoBoxPrefab.name = "Ammo Box";
        ammoBoxPrefab.textureKey = "Ammo_box";
        terminalPrefab.textureMapIndex = -1;
        ammoBoxPrefab.textureSize = { 32, 32 };
        ammoBoxPrefab.isInteractive = true;
        ammoBoxPrefab.hasCollision = false;
        ammoBoxPrefab.prompt = "Press E: Pick up Ammo";
        ammoBoxPrefab.singleUse = true;
        ammoBoxPrefab.actions =
        {
            {"Pick up", "Handler_AddAmmoBox"}
        };
        catalog.RegisterPrefab("ammo_box", ammoBoxPrefab);

        XYZEngine::LOG_INFO("Prefab setup complete");
    }
}