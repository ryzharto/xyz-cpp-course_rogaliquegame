#include "pch.h"
#include "InteractableComponent.h"

namespace XYZEngine
{
    InteractableComponent::InteractableComponent(GameObject* gameObject) : Component(gameObject) {}

    void InteractableComponent::AddAction(const std::string& name, std::function<void(GameObject*, GameObject*)> func)
    {
        actions.push_back({ name, func });
    }

    void InteractableComponent::ExecuteAction(size_t index, GameObject* instigator)
    {
        if (index < actions.size() && actions[index].execute)
            actions.at(index).execute(instigator, gameObject);

        if (singleUse)
            GameWorld::Instance()->DestroyGameObject(gameObject);
    }
}