#include "pch.h"
#include "AttackComponent.h"
#include "StatsComponent.h"
#include "TransformComponent.h"
#include <cmath>

namespace XYZEngine
{
    AttackComponent::AttackComponent(GameObject* gameObject) : Component(gameObject)
    {
        attackPower = 1.f;
        attackRange = 50.f;
        attackCooldown = 0.5f;
        timeSinceLastAttack = attackCooldown;
    }

    void AttackComponent::SetAttackPower(float newAttackPower)
    {
        attackPower = newAttackPower;
    }

    void AttackComponent::SetAttackRange(float newAttackRange)
    {
        attackRange = newAttackRange;
    }

    void AttackComponent::SetAttackCooldown(float newAttackCooldown)
    {
        attackCooldown = newAttackCooldown;
    }

    bool AttackComponent::CanAttack() const
    {
        return timeSinceLastAttack >= attackCooldown;
    }

    void AttackComponent::PerformMeleeAttack(GameObject* target)
    {
        if (!target || !CanAttack()) return;

        auto targetStats = target->GetComponent<StatsComponent>();
        if (!targetStats) return;
       
        targetStats->TakeDamage(attackPower);
        timeSinceLastAttack = 0.f; // reset timer
        LOG_INFO("Melee attack dealt " + std::to_string(attackPower) + " damage");
    }

    void AttackComponent::Attack(GameObject* target) const
    {
        if (!target)
        {
            return;
        }

        auto targetStatsComponent = target->GetComponent<StatsComponent>();
        if (targetStatsComponent)
        {
            float damage = attackPower;
            targetStatsComponent->TakeDamage(damage);
        }
    }

    void AttackComponent::Update(float deltaTime)
    {
        // Update attack cooldown timer
        if (timeSinceLastAttack < attackCooldown)
            timeSinceLastAttack += deltaTime;
    }

    void AttackComponent::Render()
    {
    }
}
