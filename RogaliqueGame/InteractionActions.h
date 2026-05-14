#pragma once
#include "GameObject.h"
#include "Prefab.h"
#include <string>
#include <unordered_map>

namespace Ryzharto_RogaliqueGame
{
    class InteractionActions
    {
    public:
        static void StorePrefab(const std::string& key, const Prefab& prefab);

        static void HackTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self);
        static void DestroyTerminal(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self);

        static void PickUpItem(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self);

    private:
        static std::unordered_map<std::string, Prefab> prefabs;
    };
}