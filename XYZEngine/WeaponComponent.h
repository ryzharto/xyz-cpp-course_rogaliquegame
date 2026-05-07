#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "Vector.h"
//#include "../RogaliqueGame/Projectile.h"

namespace XYZEngine
{
	class WeaponComponent : public Component
	{
	public:
		WeaponComponent(GameObject* gameObject);
		void Update(float deltaTime) override;
		void Render() override {}

		void SetBulletSpeed(float speed) { bulletSpeed = speed; }
		void SetDamage(float newDamage) { damage = newDamage; }
		void SetFireRate(float shotsPerSecond) { fireCooldown = 1.f / shotsPerSecond; }

		// Ammo
		void SetMaxAmmo(int ammo); // magazine capacity
		int GetCurrentAmmo() const { return currentAmmo; } 
		int GetMaxAmmo() const { return maxAmmo; }
		bool HasAmmo() const { return currentAmmo > 0; }

		// Reloading
		void Reload();
		void SetReloadTime(float time) { reloadCooldown = time; }
		float GetReloadProgress() const; // for UI
		bool IsReloading() const { return isReloading; }

	private:
		void Fire();
		void ConsumeAmmo(int count);
	
		float bulletSpeed = 600.f;
		float damage = 15.f;
		int currentAmmo = 10;
		int maxAmmo = 10;
		float fireCooldown = 0.3f; // seconds between shoots
		float timeSinceLastShot = 0.f; // shoot timer
		float reloadCooldown = 2.f; // seconds for reload
		float timeSinceReload = 0.f; // reload timer
		bool isReloading = false;
		float muzzleOffset = 100.f;

		InputManager& input = InputManager::Instance();


	};
}


