#include "pch.h"
#include "StatsComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	StatsComponent::StatsComponent(GameObject* gameObject) : Component(gameObject)
	{
		currentHealth = 100.f;
		maxHealth = 100.f;
		currentArmour = 0.f;
	}

	void StatsComponent::SetHealth(float newHealth)
	{
		currentHealth = newHealth;
		if (currentHealth >= maxHealth) currentHealth = maxHealth;
	}

	void StatsComponent::SetArmour(float newArmour)
	{
		currentArmour = newArmour;
		if (currentArmour >= maxArmour) currentArmour = maxArmour;
	}

	void StatsComponent::SetStamina(float newStamina)
	{
		currentStamina = newStamina;
		if (currentStamina >= maxStamina) currentStamina = maxStamina;
	}

	void StatsComponent::UseStamina(float amount)
	{
		currentStamina -= amount;
		if (currentStamina < 0.f) currentStamina = 0.f;
	}

	void StatsComponent::RegenStamina(float amount)
	{
		currentStamina += amount;
		if (currentStamina > maxStamina) currentStamina = maxStamina;
	}

	void StatsComponent::TakeDamage(float damage)
	{
		damage -= currentArmour; // reduce damage by current armour amount

		if (damage < 0)
		{
			damage = 0;
			return;
		}

		currentArmour -= 1.f; // loss some armour as it wears under attacks

		if (currentArmour <= 0)
		{
			currentArmour = 0;
			LOG_INFO("The armour was broken");
		}

		currentHealth -= damage;
		if (currentHealth < 0)
		{
			currentHealth = 0;
			HealthState condition = HealthState::Dead;
			LOG_INFO("YOU ARE DEAD...");
		}

		LOG_INFO("Taking " + std::to_string(damage) + " damage, current health " + std::to_string(currentHealth));
		LOG_INFO("Armour left " + std::to_string(currentArmour));
	}

	void StatsComponent::Heal(float amount)
	{
		currentHealth += amount;
		if (currentHealth >= maxHealth) currentHealth = maxHealth;

		LOG_INFO("Healed " + std::to_string(amount) + " health, current health " + std::to_string(currentHealth));
	}

	void StatsComponent::Update(float deltaTime)
	{
		// Stamina regeneration
		if (currentStamina < maxStamina)
		{
			currentStamina += staminaRegenRate * deltaTime;
			if (currentStamina > maxStamina) 
				currentStamina = maxStamina;
		}
	}

	void StatsComponent::Render()
	{
	}
}
