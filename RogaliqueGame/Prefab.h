#pragma once
#include "GameObject.h"
#include "ItemData.h"
#include "WeaponComponent.h"
#include "Vector.h"
#include <string>
#include <vector>
#include <optional>

namespace Ryzharto_RogaliqueGame
{
    struct PrefabAction // For world interactable objects
    {
        std::string actionName;   // "Hack", "Pick up"
        std::string handlerName;  // "Handler_HackTerminal"
    };

    struct Prefab
    {
        std::string key; // Catalog key
        std::string name; // "Terminal", "Medkit"
        std::string textureKey; // key at ResourceSystem
        sf::Vector2u textureSize = { 64, 64 };
        int textureMapIndex = -1; // >=0 – use as texturemap element

        bool isInteractive = false; // if true, then add InteractableComponent
        bool hasCollision = false; // if true object will collide (no - for fllors, pickables)

        ItemCategory category = ItemCategory::None;

        std::vector<ItemAction> itemActions;
        //std::vector<ItemActionType> availableActions; // inventory actions order
       // std::function<void(XYZEngine::GameObject* owner)> useEffect; // for consumables
        std::optional<XYZEngine::WeaponInfo> weaponData; // for weapons

        // Weapons
        //bool isWeapon = false;
        //std::string weaponName;

        // Interactive setting for world objects (used if isInteractive == true)
        float interactionRadius = 100.f;
        std::string prompt;
        bool singleUse = false;
        std::vector<PrefabAction> interactActions; // actions in world (Hack, destroy, etc)
    };
}