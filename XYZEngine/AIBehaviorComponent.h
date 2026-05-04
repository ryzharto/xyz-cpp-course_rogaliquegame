#pragma once
#include "GameObject.h"
#include "AttackComponent.h"
#include "FollowComponent.h"

namespace XYZEngine
{
    enum class AIState
    {
        Idle,
        Patrol,
        Chase,
        Attack,
    };

	class AIBehaviorComponent : public Component
	{
    public:
        AIBehaviorComponent(GameObject* gameObject);

        void Update(float deltaTime) override;
        void Render() override {}

        void SetTarget(GameObject* target);
        void SetDetectionRadius(float radius) { detectionRadius = radius; }
        float GetDetectionRadius() const { return detectionRadius; }
        void SetChaseSpeed(float chaseSpeed);

    private:
        GameObject* target = nullptr;
        TransformComponent* transform = nullptr;
        AttackComponent* attackComponent = nullptr;
        FollowComponent* followComponent = nullptr;

        float detectionRadius = 500.f;
        float speed = 50.f;
        float chaseSpeed = 100.f;

        AIState currentState = AIState::Idle;
	};
}


