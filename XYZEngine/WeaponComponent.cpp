#include "pch.h"
#include "WeaponComponent.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "SpriteComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "StatsComponent.h"
#include "RenderSystem.h"
#include "../RogaliqueGame/Projectile.h"

namespace XYZEngine
{
	WeaponComponent::WeaponComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void WeaponComponent::Update(float deltaTime)
	{
		if (!active) return;

		if (isReloading)
		{
			timeSinceReload -= deltaTime;

			if (timeSinceReload <= 0.f)
			{
				auto& info = weapons[currentIndex];
				info.currentAmmo = info.maxAmmo;
				isReloading = false;
				LOG_INFO("Reload complete. Ammo: " + std::to_string(info.currentAmmo));
			}
			return; 
		}

		timeSinceLastShot += deltaTime;

		// Switch weapon on mouse wheel
		if (input.GetMouseWheelDelta() != 0)
		{
			if (input.GetMouseWheelDelta() > 0)
				SwitchToNextWeapon();
			else
				SwitchToPrevWeapon();
		}

		// Reloading (if not melee)
		if (input.IsReloadButtonPressed() && !GetCurrentWeaponInfo().isMelee)
		{
			Reload();
		}

		// Attack
		if (input.IsMouseLeftButtonPressed() && timeSinceLastShot >= fireCooldown)
		{
			if (GetCurrentWeaponInfo().isMelee)
				PerformMelee();
			else if (HasAmmo())
				FireRanged();
			timeSinceLastShot = 0;
		}
	}

	void WeaponComponent::AddWeapon(const WeaponInfo& info)
	{
		// Dont add by name
		for (auto& weapon : weapons)
			if (weapon.name == info.name) return;

		WeaponInfo newWeapon = info;

		if (newWeapon.currentAmmo <= 0)
			newWeapon.currentAmmo = info.maxAmmo;

		weapons.push_back(newWeapon);
		// If this weapon is first one - initialize
		if (weapons.size() == 1)
		{
			currentIndex = 0;
			const auto& current = weapons[0];
			damage = current.damage;
			fireCooldown = 1.f / current.fireRate;
			bulletSpeed = current.bulletSpeed;
		}
		LOG_INFO("Weapon added: " + info.name + " ammo: " + std::to_string(newWeapon.currentAmmo));
		LOG_INFO("AddWeapon received name: " + info.name + " icon: " + (info.icon ? "yes" : "no"));
	}

	void WeaponComponent::RemoveWeapon(const std::string& name)
	{
		LOG_INFO("RemoveWeapon called for " + name + ", current weapons count: " + std::to_string(weapons.size()));
		auto it = std::find_if(weapons.begin(), weapons.end(), [&name](const WeaponInfo& w) { return w.name == name; });
		if (it != weapons.end())
		{
			size_t idx = std::distance(weapons.begin(), it);
			weapons.erase(it);

			if (idx <= currentIndex && currentIndex > 0)
				currentIndex--;

			if (!weapons.empty())
			{
				const auto& current = weapons[currentIndex];
				damage = current.damage;
				fireCooldown = 1.f / current.fireRate;
				bulletSpeed = current.bulletSpeed;
			}	
			LOG_INFO("Weapon remowed: " + name + ", remaining: " + std::to_string(weapons.size()));
		}
	}

	const WeaponInfo& WeaponComponent::GetCurrentWeaponInfo() const
	{
		return weapons[currentIndex];
	}

	void WeaponComponent::SwitchToNextWeapon()
	{
		if (weapons.empty()) return;

		currentIndex = (currentIndex + 1) % weapons.size();
		const WeaponInfo& current = weapons[currentIndex];
		isReloading = false;
		damage = current.damage;
		fireCooldown = 1.f / current.fireRate;
		bulletSpeed = current.bulletSpeed;

		LOG_INFO("Switched to next weapon: " + current.name);
	}

	void WeaponComponent::SwitchToPrevWeapon()
	{
		if (weapons.empty()) return;

		if (currentIndex == 0)
			currentIndex = weapons.size() - 1;
		else
			currentIndex--;

		const WeaponInfo& current = weapons[currentIndex];
		isReloading = false;
		damage = current.damage;
		fireCooldown = 1.f / current.fireRate;
		bulletSpeed = current.bulletSpeed;

		LOG_INFO("Switched to previous weapon: " + current.name);
	}

	void WeaponComponent::SetCurrentWeaponIndex(int index)
	{
		if (index >= 0 && index < weapons.size()) currentIndex = index;
	}

	bool WeaponComponent::HasWeapon(const std::string& name) const
	{
		for (const auto& w : weapons)
			if (w.name == name) return true;
		return false;
	}

	void WeaponComponent::SetCurrentAmmo(int ammo)
	{
		if (!weapons.empty())
			weapons[currentIndex].currentAmmo = ammo;
	}

	void WeaponComponent::SetMaxAmmo(int ammo)
	{
		auto& info = weapons[currentIndex];
		info.maxAmmo += ammo;
		info.currentAmmo = info.maxAmmo;
	}

	void WeaponComponent::Reload()
	{
		if (isReloading) return; // already reloading

		auto& info = weapons[currentIndex];
		if (info.currentAmmo == info.maxAmmo) return;
			
		isReloading = true;
		timeSinceReload = GetCurrentWeaponInfo().reloadTime;

		LOG_INFO("RELOADING...");
	}

	float WeaponComponent::GetReloadProgress() const
	{
		if (!isReloading) return 0.f;
		return 1.f - (timeSinceReload / reloadCooldown);
	}

	void WeaponComponent::FireRanged()
	{
		if (!HasAmmo()) return;

		auto transform = gameObject->GetComponent<TransformComponent>();

		if (!transform) return;

		Vector2Df playerPos = transform->GetWorldPosition();
		sf::Vector2f mouseWorldPos = input.GetMouseWorldPosition();
		Vector2Df direction = { mouseWorldPos.x - playerPos.x, mouseWorldPos.y - playerPos.y };
		float length = direction.GetLength();

		if (length < 0.001f) return;
		direction.x /= length;
		direction.y /= length;

		// Bullet creation
		ConsumeAmmo(1);
		new Ryzharto_RogaliqueGame::Projectile((playerPos + direction * muzzleOffset), "Bullet", direction, gameObject, damage);
	}

	void WeaponComponent::PerformMelee()
	{
		attackComponent = gameObject->GetComponent<XYZEngine::AttackComponent>();
		if (!attackComponent) return;

		auto* transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		if (!transform) return;
		
		Vector2Df myPos = transform->GetWorldPosition();
		float attackRadius = attackComponent->GetAttackRange();

		GameObject* closestEnemy = nullptr;
		float minDistSq = attackRadius * attackRadius;

		for (auto& go : GameWorld::Instance()->GetGameObjects())
		{
			if (go == gameObject) continue;
			auto* stats = go->GetComponent<XYZEngine::StatsComponent>();
			if (!stats) continue;
			auto* goTransform = go->GetComponent<XYZEngine::TransformComponent>();
			if (!goTransform) continue;

			Vector2Df pos = goTransform->GetWorldPosition();
			float dx = pos.x - myPos.x;
			float dy = pos.y - myPos.y;
			float distSq = dx * dx + dy * dy;

			if (distSq < minDistSq)
			{
				closestEnemy = go;
				minDistSq = distSq;
			}
		}

		if (closestEnemy)
		{
			attackComponent->PerformMeleeAttack(closestEnemy);
			LOG_INFO("WeaponComponent::PerformMelee(): Player melee attack dealt damage to " + closestEnemy->GetName());
		}

	}

	void WeaponComponent::ConsumeAmmo(int count)
	{
		auto& info = weapons[currentIndex];
		info.currentAmmo -= count;
		if (info.currentAmmo <= 0)
		{
			info.currentAmmo = 0;
			LOG_INFO("Out of ammo");
		}
		LOG_INFO("Ammo left: " + std::to_string(info.currentAmmo));
	}
}