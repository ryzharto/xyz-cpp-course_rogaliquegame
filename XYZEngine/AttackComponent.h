#pragma once
#include "GameObject.h"

namespace XYZEngine
{
    class AttackComponent : public Component
    {
    public:
        AttackComponent(GameObject* gameObject);

        float GetAttackPower() const { return attackPower; }
        void SetAttackPower(float newAttackPower);

        float GetAttackRange() const { return attackRange; }
        void SetAttackRange(float newAttackRange);

        float GetAttackCooldown() const { return attackCooldown; }
        void SetAttackCooldown(float newAttackCooldown);

        bool CanAttack() const;
        void PerformMeleeAttack(GameObject* target);

        void Attack(GameObject* target) const;

        void Update(float deltaTime) override;
        void Render() override;

    private:
        float attackPower;
        float attackRange;
        float attackCooldown;
        float timeSinceLastAttack;
    };
}


