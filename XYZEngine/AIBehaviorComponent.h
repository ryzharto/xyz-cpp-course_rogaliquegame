#pragma once
#include "GameObject.h"
#include "TransformComponent.h"
#include "AttackComponent.h"
#include "FollowComponent.h"
#include "StatsComponent.h"

namespace XYZEngine
{
    enum class AIState
    {
        Idle,
        Patrol,
        Chase,
        Attack,
        Dead,
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
        StatsComponent* stats = nullptr;

        float detectionRadius = 500.f;
        float speed = 50.f;
        float chaseSpeed = 100.f;

        AIState currentState = AIState::Idle;
	};
}


