#include "EnemyRaptor.h"
#include "ResourceSystem.h"
#include "SpriteComponent.h"
#include "SpriteDirectionComponent.h"
#include "FollowComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "StatsComponent.h"
#include "AttackComponent.h"
#include "AIBehaviorComponent.h"

namespace Ryzharto_RogaliqueGame
{
	EnemyRaptor::EnemyRaptor(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* targetToFollow) : Enemy(position, targetToFollow)
	{
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		// Sprite
		auto sprite = gameObject->GetComponent<XYZEngine::SpriteComponent>();
		sprite->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Raptor_biege"));
		sprite->SetPixelSize(150, 70);

		// Following
		auto follower = gameObject->GetComponent<XYZEngine::FollowComponent>();	

		// Physics
		auto rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		//Stats
		auto aiStats = gameObject->GetComponent<XYZEngine::StatsComponent>();
		aiStats->SetHealth(100.f);

		// Attack
		auto attack = gameObject->GetComponent<XYZEngine::AttackComponent>();
		attack->SetAttackRange(150.f);
		attack->SetAttackPower(10.f);
		attack->SetAttackCooldown(1.0f);

		// AI behavior
		auto behavior = gameObject->GetComponent<XYZEngine::AIBehaviorComponent>();
		behavior->SetDetectionRadius(500.f);
		behavior->SetChaseSpeed(120.f);
		behavior->SetTarget(targetToFollow);
	}
}