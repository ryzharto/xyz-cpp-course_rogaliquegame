#include "PrefabSetup.h"
#include "PrefabCatalog.h"
#include "InventoryActions.h"
#include "InteractionActions.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    void SetupPrefabs()
    {
        auto& catalog = PrefabCatalog::Instance();

        // ---------- Register Handlers ----------
        catalog.RegisterHandler("Handler_HackTerminal", InteractionActions::HackTerminal);
        catalog.RegisterHandler("Handler_DestroyTerminal", InteractionActions::DestroyTerminal);
        catalog.RegisterHandler("Handler_AddMedkit", InteractionActions::PickUpMedkit);
        catalog.RegisterHandler("Handler_AddAmmoBox", InteractionActions::PickUpAmmoBox);

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
        terminalPrefab.actions =
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
        medkitPrefab.isInteractive = true;
        medkitPrefab.hasCollision = false;
        medkitPrefab.interactionRadius = 30.f;
        medkitPrefab.prompt = "Pick up Medkit";
        medkitPrefab.singleUse = true;
        medkitPrefab.actions =
        {
            {"Pick up", "Handler_AddMedkit"}
        };
        catalog.RegisterPrefab(medkitPrefab.key, medkitPrefab);
        InteractionActions::StorePrefab(medkitPrefab.key, medkitPrefab);

        Prefab ammoBoxPrefab;
        ammoBoxPrefab.key = "ammo_box";
        ammoBoxPrefab.name = "Ammo Box";
        ammoBoxPrefab.textureKey = "Ammo_box";
        ammoBoxPrefab.textureMapIndex = -1;
        ammoBoxPrefab.textureSize = { 32, 32 };
        ammoBoxPrefab.isInteractive = true;
        ammoBoxPrefab.hasCollision = false;
        ammoBoxPrefab.interactionRadius = 30.f;
        ammoBoxPrefab.prompt = "Pick up Ammo";
        ammoBoxPrefab.singleUse = true;
        ammoBoxPrefab.actions =
        {
            {"Pick up", "Handler_AddAmmoBox"}
        };
        catalog.RegisterPrefab(ammoBoxPrefab.key, ammoBoxPrefab);
        InteractionActions::StorePrefab(ammoBoxPrefab.key, ammoBoxPrefab);

        XYZEngine::LOG_INFO("Prefab setup complete");
    }
}