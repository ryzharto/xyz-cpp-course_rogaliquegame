#include "PrefabCatalog.h"
#include "GameWorld.h"
#include "SpriteComponent.h"
#include "InteractableComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    PrefabCatalog& PrefabCatalog::Instance()
    {
        static PrefabCatalog instance;
        return instance;
    }

    void PrefabCatalog::RegisterPrefab(const std::string& key, const Prefab& prefab)
    {
        prefabs[key] = prefab;
        XYZEngine::LOG_INFO("Prefab registered: " + key);
    }

    void PrefabCatalog::RegisterHandler(const std::string& handlerName, PrefabActionHandler handler)
    {
        handlers[handlerName] = handler;
        XYZEngine::LOG_INFO("Handler registered: " + handlerName);
    }

    XYZEngine::GameObject* PrefabCatalog::Instantiate(const std::string& key, const XYZEngine::Vector2Df& position) const
    {
        auto it = prefabs.find(key);
        if (it == prefabs.end())
        {
            XYZEngine::LOG_ERROR("Prefab key '" + key + "' not found in catalog");
            return nullptr;
        }

        const Prefab& prefab = it->second;
        auto* go = XYZEngine::GameWorld::Instance()->CreateGameObject(prefab.name);
        auto* transform = go->GetComponent<XYZEngine::TransformComponent>();
        transform->SetWorldPosition(position);

        const sf::Texture* texture = nullptr;

        if (prefab.textureMapIndex >= 0)
        {
            // 1. Search in TextureMap
            texture = XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared(
                prefab.textureKey, prefab.textureMapIndex);
            if (texture == nullptr)
                XYZEngine::LOG_WARN("Texture map element '" + prefab.textureKey +
                    "[" + std::to_string(prefab.textureMapIndex) + "]' not found");
        }
        else
        {
            // 2. Search as Texture
            texture = XYZEngine::ResourceSystem::Instance()->GetTextureShared(prefab.textureKey);
            if (texture == nullptr)
                XYZEngine::LOG_WARN("Texture '" + prefab.textureKey + "' not found in shared textures");
        }

        if (texture == nullptr)
        {
            XYZEngine::LOG_ERROR("No texture found for prefab '" + key + "'");
            return nullptr;
        }

        // Rigidboy
        auto rigidbody = go->AddComponent<XYZEngine::RigidbodyComponent>();
        rigidbody->SetKinematic(true);

        // Sprite
        auto* sprite = go->AddComponent<XYZEngine::SpriteComponent>();
        //const sf::Texture* texture = nullptr;

        sprite->SetTexture(*texture);
        sprite->SetPixelSize(prefab.textureSize.x, prefab.textureSize.y);

        // Base static collision
        if (prefab.hasCollision)
        {
            auto* collider = go->AddComponent<XYZEngine::SpriteColliderComponent>();
            collider->SetStatic(true);
        }

        // Interaction
        if (prefab.isInteractive)
        {
            auto* interact = go->AddComponent<XYZEngine::InteractableComponent>();
            interact->SetInteractionRadius(prefab.interactionRadius);
            interact->SetPrompt(prefab.prompt);
            if (prefab.singleUse)
                interact->SetOneShot(true);

            for (const auto& action : prefab.actions)
            {
                auto handlerIt = handlers.find(action.handlerName);
                if (handlerIt != handlers.end())
                {
                    interact->AddAction(action.actionName, handlerIt->second);
                }
                else
                {
                    XYZEngine::LOG_WARN("Handler '" + action.handlerName + "' not registered for prefab '" + key + "'");
                }
            }
        }

        XYZEngine::LOG_INFO("Prefab '" + key + "' instantiated at (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");
        return go;
    }
}