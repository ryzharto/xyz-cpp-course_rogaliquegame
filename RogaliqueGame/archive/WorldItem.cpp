#include "WorldItem.h"
#include "GameWorld.h"
#include "SpriteComponent.h"
#include "ResourceSystem.h"
#include "InteractableComponent.h"
#include "InventoryComponent.h"
#include "StatsComponent.h"
#include "WeaponComponent.h"

namespace Ryzharto_RogaliqueGame
{
    WorldItem::WorldItem(const XYZEngine::Vector2Df& position, const Item& item, const std::string& textureName)
    {
        gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject(item.name); //"WorldItem_" + item.name
        auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
        transform->SetWorldPosition(position);

        auto sprite = gameObject->AddComponent<XYZEngine::SpriteComponent>();
        sprite->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared(textureName));
        sprite->SetPixelSize(32, 32);

        auto interact = gameObject->AddComponent<XYZEngine::InteractableComponent>();
        interact->SetPrompt("Pick up " + item.name);
        interact->SetOneShot(true);
        interact->AddAction("Pick up", [item](XYZEngine::GameObject* instigator, XYZEngine::GameObject* self)
            {
            auto inventory = instigator->GetComponent<XYZEngine::InventoryComponent>();
            if (inventory)
                inventory->AddItem(item);
            });
    }
}