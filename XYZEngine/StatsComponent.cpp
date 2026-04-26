#include "pch.h"
#include "StatsComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	StatsComponent::StatsComponent(GameObject* gameObject) : Component(gameObject)
	{
		currentHealth = 100.f;
		maxHealth = 100.f;
		armour = 0.f;
	}

	void StatsComponent::SetHealth(float newHealth)
	{
		currentHealth = newHealth;
	}

	void StatsComponent::SetArmour(float newArmour)
	{
		armour = newArmour;
	}

	void StatsComponent::TakeDamage(float damage)
	{
		damage -= armour;
		if (damage < 0)
		{
			damage = 0;
		}

		armour -= 1.f;
		LOG_INFO("Armour left " + std::to_string(armour));

		if (armour < 0)
		{
			armour = 0;
			LOG_INFO("The armour was broken");
		}

		currentHealth -= damage;
		if (currentHealth < 0)
		{
			currentHealth = 0;
		}

		LOG_INFO("Taking" + std::to_string(damage) + " damage, current health " + std::to_string(currentHealth));
	}

	void StatsComponent::Heal(float amount)
	{
		currentHealth += amount;
		if (currentHealth >= maxHealth)
		{
			currentHealth = maxHealth;
		}

		LOG_INFO("Healed" + std::to_string(amount) + " health, current health " + std::to_string(currentHealth));
	}

	void StatsComponent::Update(float deltaTime)
	{
	}

	void StatsComponent::Render()
	{
	}
}
