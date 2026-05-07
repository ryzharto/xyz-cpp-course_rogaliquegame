#pragma once
#include "GameObject.h"

namespace XYZEngine
{
	enum class HealthState
	{
		Fine,
		Good,
		Warning,
		Danger,
		Dead,
	};

	class StatsComponent : public Component
	{
	public:
		StatsComponent(GameObject* gameObject);

		void SetHealth(float newHealth);
		float GetCurrentHealth() const { return currentHealth; }
		float GetMaxHealth() const { return maxHealth; }

		void SetArmour(float newArmour);
		float GetCurrentArmour() const { return currentArmour; }
		float GetMaxArmour() const { return maxArmour; }

		float GetCurrentStamina() const { return currentStamina;  }
		float GetMaxStamina() const { return maxStamina; }
		
		void UseStamina(float amount);
		void RegenStamina(float amount);

		void TakeDamage(float damage);
		void Heal(float amount);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		HealthState condition = HealthState::Fine;
		float maxHealth = 100.f;
		float currentHealth = 100.f;
		float maxStamina = 100.f;
		float currentStamina = 100.f;
		float staminaRegenRate = 10.f; // points per second
		float currentArmour = 100.f;
		float maxArmour = 100.f;
	};
}