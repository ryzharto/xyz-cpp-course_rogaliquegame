#pragma once
#include "Component.h"
#include "GameWorld.h"
#include <vector>
#include <string>
#include <functional>

namespace XYZEngine
{
	class GameObject;

	struct InteractAction
	{
		std::string name;
		std::function<void(GameObject* owner, GameObject* interactable)> execute;
	};

	class InteractableComponent : public Component
	{
	public: 
        InteractableComponent(GameObject* gameObject);

        void AddAction(const std::string& name, std::function<void(GameObject*, GameObject*)> func);
        const std::vector<InteractAction>& GetActions() const { return actions; }
        void ExecuteAction(size_t index, GameObject* instigator);

        void SetInteractionRadius(float r) { radius = r; }
        float GetInteractionRadius() const { return radius; }

        void SetOneShot(bool singleuse) { singleUse = singleuse; }
        bool IsOneShot() const { return singleUse; }

        // Hind (for UI)
        void SetPrompt(const std::string& newPrompt) { prompt = newPrompt; }
        const std::string& GetPrompt() const { return prompt; }

        void Update(float deltaTime) override {}
        void Render() override {}

    private:
        std::vector<InteractAction> actions;
        float radius = 50.f;
        bool singleUse = false; // 
        std::string prompt;
	};
}

