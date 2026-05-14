#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "AttackComponent.h"
#include "Vector.h"
#include <vector>

namespace XYZEngine
{
	struct WeaponInfo
	{
		std::string name;           // "Machete", "Rifle"
		const sf::Texture* icon = nullptr; // texture for HUD
		//std::string iconTexture;    // texture key for HUD
		float damage = 10.f;
		float fireRate = 0.3f;      // fires per second (ranged)
		int maxAmmo = 10;
		int currentAmmo = 0;
		float reloadTime = 2.f;
		float bulletSpeed = 600.f;  // for ranged
		bool isMelee = false;       // true Ц melee
	};

	class WeaponComponent : public Component
	{
	public:
		WeaponComponent(GameObject* gameObject);
		void Update(float deltaTime) override;
		void Render() override {}

		// ƒобавить оружие в арсенал (если такое же им€ уже есть Ц не добавл€ем)
		void AddWeapon(const WeaponInfo& info);
		void RemoveWeapon(const std::string& name);
		const WeaponInfo& GetCurrentWeaponInfo() const;
		void SwitchToNextWeapon();
		void SwitchToPrevWeapon();
		int GetCurrentWeaponIndex() const { return currentIndex; }
		bool HasWeapon(const std::string& name) const;
		void SetActive(bool newActive) { active = newActive; }
		bool isActive() const { return active; }
			
		// Ammo
		void SetCurrentAmmo(int ammo);
		void SetMaxAmmo(int ammo); // magazine capacity
		int GetCurrentAmmo() const { return weapons[currentIndex].currentAmmo; } 
		int GetMaxAmmo() const { return GetCurrentWeaponInfo().maxAmmo; }
		bool HasAmmo() const { return GetCurrentAmmo() > 0; }

		void SetBulletSpeed(float speed) { bulletSpeed = speed; }
		void SetDamage(float newDamage) { damage = newDamage; }
		void SetFireRate(float shotsPerSecond) { fireCooldown = 1.f / shotsPerSecond; }

		// Reloading
		void Reload();
		void SetReloadTime(float time) { reloadCooldown = time; }
		float GetReloadProgress() const; // for UI
		bool IsReloading() const { return isReloading; }

	private:
		void FireRanged();
		void PerformMelee();
		void ConsumeAmmo(int count);
	
		std::vector<WeaponInfo> weapons;
		size_t currentIndex = 0;

		float bulletSpeed = 600.f;
		float damage = 15.f;
		//int currentAmmo = 10;
		int maxAmmo = 10;
		float fireCooldown = 0.3f; // seconds between shoots
		float timeSinceLastShot = 0.f; // shoot timer
		float reloadCooldown = 2.f; // seconds for reload
		float timeSinceReload = 0.f; // reload timer
		bool isReloading = false;
		bool active = true;
		float muzzleOffset = 75.f;

		InputManager& input = InputManager::Instance();
		AttackComponent* attackComponent = nullptr;

	};
}


