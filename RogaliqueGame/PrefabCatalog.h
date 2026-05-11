#pragma once
#include "Prefab.h"
#include "GameObject.h"
#include <unordered_map>
#include <functional>

namespace Ryzharto_RogaliqueGame
{
    using PrefabActionHandler = void(*)(XYZEngine::GameObject* instigator, XYZEngine::GameObject* self);

    class PrefabCatalog
    {
    public:
        static PrefabCatalog& Instance();

        void RegisterPrefab(const std::string& key, const Prefab& prefab);
        void RegisterHandler(const std::string& handlerName, PrefabActionHandler handler);

        XYZEngine::GameObject* Instantiate(const std::string& key, const XYZEngine::Vector2Df& position) const;

    private:
        PrefabCatalog() = default;
        std::unordered_map<std::string, Prefab> prefabs;
        std::unordered_map<std::string, PrefabActionHandler> handlers;
    };
}