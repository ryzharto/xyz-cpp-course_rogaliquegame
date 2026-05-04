#include "AI.h"
#include "ResourceSystem.h"
#include <SpriteColliderComponent.h>
#include "MovementComponent.h"
#include "SpriteDirectionComponent.h"
#include <FollowComponent.h>
#include <StatsComponent.h>
#include <AttackComponent.h>
#include "AIBehaviorComponent.h"

namespace Ryzharto_RogaliqueGame
{
	AI::AI(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto sprite = gameObject->AddComponent<XYZEngine::SpriteComponent>();
		sprite->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Raptor_biege"));
		sprite->SetPixelSize(200, 100);

		auto aiInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto spriteDirection = gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

		auto follower = gameObject->AddComponent<XYZEngine::FollowComponent>();
		follower->SetSpeed(120.f);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto aiStats = gameObject->AddComponent<XYZEngine::StatsComponent>();

		auto attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetAttackPower(5.f);
		attack->SetAttackRange(150.f);
		attack->SetAttackCooldown(1.2f);

		auto behavior = gameObject->AddComponent<XYZEngine::AIBehaviorComponent>();
		behavior->SetDetectionRadius(500.f);
		behavior->SetChaseSpeed(100.f);
		behavior->SetTarget(player);

		XYZEngine::LOG_INFO("AI GameObject constructed with components: Transform, SpriteRenderer, Input, SpriteDirection, Follow, Rigidbody, Collider");
	}

	XYZEngine::GameObject* AI::GetGameObject()
	{
		return gameObject;
	}
}