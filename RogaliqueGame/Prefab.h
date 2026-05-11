#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
    struct PrefabAction
    {
        std::string actionName;   // "Hack", "Pick up"
        std::string handlerName;  // "Handler_HackTerminal"
    };

    struct Prefab
    {
        std::string name; // "Terminal", "Medkit"
        std::string textureKey; // key at ResourceSystem
        sf::Vector2u textureSize = { 64, 64 };
        int textureMapIndex = -1; // >=0 – use as texturemap element

        bool isInteractive = false; // if true, then add InteractableComponent
        bool hasCollision = false; // if true object will collide (no - for fllors, pickables)

        // Interactive setting (used if isInteractive == true)
        float interactionRadius = 100.f;
        std::string prompt;
        bool singleUse = false;
        std::vector<PrefabAction> actions;
    };
}