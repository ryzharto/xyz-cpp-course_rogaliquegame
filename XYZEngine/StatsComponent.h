#pragma once
#include "GameObject.h"

namespace XYZEngine
{
	class StatsComponent : public Component
	{
	public:
		StatsComponent(GameObject* gameObject);

		float GetCurrentHealth() const { return currentHealth; };
		float GetMaxHealth() const { return maxHealth; };
		float GetArmour() const { return armour; };

		void SetHealth(float newHealth);
		void SetArmour(float newArmour);

		void TakeDamage(float damage);
		void Heal(float amount);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		float maxHealth;
		float currentHealth;
		float armour;
	};
}