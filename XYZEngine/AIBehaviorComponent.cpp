#include "pch.h"
#include "AIBehaviorComponent.h"
#include "TransformComponent.h"
#include "AttackComponent.h"
#include "StatsComponent.h"
#include "GameWorld.h"

namespace XYZEngine
{
    AIBehaviorComponent::AIBehaviorComponent(GameObject* gameObject) : Component(gameObject), target(nullptr)
    {
        transform = gameObject->GetComponent<TransformComponent>();
        attackComponent = gameObject->GetComponent<AttackComponent>();

        if (!transform)
            LOG_WARN("AIBehaviorComponent requires TransformComponent");
        if (!attackComponent)
            LOG_WARN("AIBehaviorComponent works better with AttackComponent");
    }

    void AIBehaviorComponent::SetTarget(GameObject* newTarget)
    {
        target = newTarget;
    }

    void AIBehaviorComponent::Update(float deltaTime)
    {
        if (!target || !attackComponent || !transform)
            return;

        auto targetTransform = target->GetComponent<TransformComponent>();
        if (!targetTransform)
            return;

        float distance = (targetTransform->GetWorldPosition() - transform->GetWorldPosition()).GetLength();
        if (distance <= attackComponent->GetAttackRange())
        {
            attackComponent->PerformMeleeAttack(target);
        }
    }
}