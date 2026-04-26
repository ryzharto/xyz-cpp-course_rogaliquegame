#pragma once
#include "GameObject.h"
#include "AttackComponent.h"

namespace XYZEngine
{
	class AIBehaviorComponent : public Component
	{
    public:
        AIBehaviorComponent(GameObject* gameObject);

        void Update(float deltaTime) override;
        void Render() override {}

        void SetTarget(GameObject* target);

    private:
        GameObject* target;
        AttackComponent* attackComponent;
        TransformComponent* transform;
	};
}


