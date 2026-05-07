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
		if (isReloading)
		{
			timeSinceReload -= deltaTime;

			if (timeSinceReload <= 0.f)
			{
				currentAmmo = maxAmmo;
				isReloading = false;
				LOG_INFO("Reload complete. Ammo: " + std::to_string(currentAmmo));
			}
			return; 
		}

		timeSinceLastShot += deltaTime;

		if (input.IsReloadButtonPressed())
		{
			Reload();
		}

		if (input.IsMouseLeftButtonPressed() && timeSinceLastShot >= fireCooldown)
		{
			Fire();
			timeSinceLastShot = 0;
		}
	}

	void WeaponComponent::SetMaxAmmo(int ammo)
	{
		maxAmmo = ammo;
		currentAmmo = maxAmmo;
	}

	void WeaponComponent::Reload()
	{
		if (isReloading)
		{
			LOG_INFO("Reloading is in progress");
			return; // already reloading
		}
		if (currentAmmo == maxAmmo)
		{
			LOG_INFO("Max ammo. No need to reloading");
			return;
		}
			
		isReloading = true;
		timeSinceReload = reloadCooldown;

		LOG_INFO("RELOADING...");
	}

	float WeaponComponent::GetReloadProgress() const
	{
		if (!isReloading) return 0.f;
		return 1.f - (timeSinceReload / reloadCooldown);
	}

	void WeaponComponent::Fire()
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
		new Ryzharto_RogaliqueGame::Projectile((playerPos + direction * muzzleOffset), "Bullet", direction, gameObject, damage);
		ConsumeAmmo(1);
	}

	void WeaponComponent::ConsumeAmmo(int count)
	{
		currentAmmo -= count;
		if (currentAmmo <= 0)
		{
			currentAmmo = 0;
			LOG_INFO("Out of ammo");
		}
	}
}