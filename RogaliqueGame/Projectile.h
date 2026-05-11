#pragma once
#include "GameObject.h"
#include "GameWorld.h"
#include "Collision.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
	class Projectile
	{
	public:
		Projectile(const XYZEngine::Vector2Df& position, std::string projectileType, const XYZEngine::Vector2Df& velocity, XYZEngine::GameObject* owner, float newDamage);
		XYZEngine::GameObject* GetGameObject() { return gameObject; }

	private:
		void OnProjectileCollision(XYZEngine::Collision collision);

		XYZEngine::GameObject* gameObject = nullptr;
		XYZEngine::GameObject* owner = nullptr;
		float damage;
	};
}


