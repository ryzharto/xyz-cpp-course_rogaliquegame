#pragma once
#include "GameObject.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
    struct Item;

    class WorldItem
    {
    public:
        WorldItem(const XYZEngine::Vector2Df& position, const Item& item, const std::string& textureName);
        XYZEngine::GameObject* GetGameObject() const { return gameObject; }
    private:
        XYZEngine::GameObject* gameObject;
    };
}
