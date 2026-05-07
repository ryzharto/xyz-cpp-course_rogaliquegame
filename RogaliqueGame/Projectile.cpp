#include "Projectile.h"
#include "ResourceSystem.h"
#include "SpriteComponent.h"
#include "LifetimeComponent.h"
#include "SpriteColliderComponent.h"
#include "StatsComponent.h"
#include <cmath>

namespace Ryzharto_RogaliqueGame
{
	Projectile::Projectile(const XYZEngine::Vector2Df& position, std::string projectileType, const XYZEngine::Vector2Df& velocity, XYZEngine::GameObject* owner, float newDamage)
	{
		// GameObject
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Projectile");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		// Selfdestruct
		auto lifetime = gameObject->AddComponent<XYZEngine::LifetimeComponent>();
		lifetime->SetLifetime(3.f);

		// Sprite
		auto sprite = gameObject->AddComponent<XYZEngine::SpriteComponent>();
		sprite->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared(projectileType));
		sprite->SetPixelSize(60, 12);

		// Physics
		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(true);
		rigidbody->SetLinearVelocity(velocity);

		float angle = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159265f;
		transform->SetWorldRotation(angle);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		if (collider)
		{
			collider->SubscribeCollision([this](XYZEngine::Collision col) {OnProjectileCollision(col); });
		}

		damage = newDamage;

		XYZEngine::LOG_INFO("Projectile created");
	}

	void Projectile::OnProjectileCollision(XYZEngine::Collision collision)
	{
		// Define collision object
		XYZEngine::ColliderComponent* otherCol = (collision.first == gameObject->GetComponent<XYZEngine::ColliderComponent>()) ? collision.second : collision.first;
		XYZEngine::GameObject* otherObj = otherCol->GetGameObject();

		// Ignore projectile owner
		if (otherObj == owner) return;

		// Apply damage if object have StatsComponent
		auto stats = otherObj->GetComponent<XYZEngine::StatsComponent>();
		if (stats)
		{
			stats->TakeDamage(damage);
			XYZEngine::LOG_INFO("Projectile hit for " + std::to_string(damage) + " damage");
		}

		// Destroy projectile
		XYZEngine::GameWorld::Instance()->DestroyGameObject(gameObject);
	}

}