#include "pch.h"
#include "AIBehaviorComponent.h"
#include "TransformComponent.h"
#include "StatsComponent.h"

namespace XYZEngine
{
    AIBehaviorComponent::AIBehaviorComponent(GameObject* gameObject) : Component(gameObject), target(nullptr)
    {
        transform = gameObject->GetComponent<TransformComponent>();
        attackComponent = gameObject->GetComponent<AttackComponent>();
        followComponent = gameObject->GetComponent<FollowComponent>();

        if (!transform)
            LOG_WARN("AIBehaviorComponent requires TransformComponent");
        if (!attackComponent)
            LOG_WARN("AIBehaviorComponent works better with AttackComponent");
        if (!followComponent)
            LOG_WARN("AIBehaviorComponent works better with FollowComponent");
    }

    void AIBehaviorComponent::SetTarget(GameObject* newTarget)
    {
        target = newTarget;
    }

    void AIBehaviorComponent::SetChaseSpeed(float newChaseSpeed)
    {
        chaseSpeed = newChaseSpeed;
    }

    void AIBehaviorComponent::Update(float deltaTime)
    {
        if (!target || !transform  || !attackComponent)
            return;

        auto targetTransform = target->GetComponent<TransformComponent>();
        if (!targetTransform)
            return;

        float distance = (targetTransform->GetWorldPosition() - transform->GetWorldPosition()).GetLength();
        float attackRange = attackComponent->GetAttackRange();

        // Changing states depending on distance
        if (distance <= attackRange && attackComponent->CanAttack())
        {
            currentState = AIState::Attack;
        }
        else if (distance <= detectionRadius)
        {
            currentState = AIState::Chase;
        }
        else
        {
            currentState = AIState::Idle;
        }

        // Actions depending on state
        switch (currentState)
        {
        case AIState::Idle:
            if (followComponent)
                followComponent->SetSpeed(0.f); // stand still
            break;

        case AIState::Chase:
            if (followComponent)
            {
                followComponent->SetTarget(target);
                followComponent->SetSpeed(chaseSpeed);
            }
            break;

        case AIState::Attack:
            if (followComponent)
                followComponent->SetSpeed(0.f);
            attackComponent->PerformMeleeAttack(target);
            break;
        }
    }
}