#include "Enemy.h"
#include "GameWorld.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "InputComponent.h"
#include "SpriteComponent.h"
#include "SpriteDirectionComponent.h"
#include "SpriteColliderComponent.h"
#include "FollowComponent.h"
#include "StatsComponent.h"
#include "AttackComponent.h"
#include "AIBehaviorComponent.h"

namespace Ryzharto_RogaliqueGame
{
	Enemy::Enemy(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* targetToFollow)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto sprite = gameObject->AddComponent<XYZEngine::SpriteComponent>();

		auto aiInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto spriteDirection = gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

		auto follower = gameObject->AddComponent<XYZEngine::FollowComponent>();
		follower->SetTarget(targetToFollow);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto aiStats = gameObject->AddComponent<XYZEngine::StatsComponent>();

		auto attack = gameObject->AddComponent<XYZEngine::AttackComponent>();

		auto behavior = gameObject->AddComponent<XYZEngine::AIBehaviorComponent>();

		XYZEngine::LOG_INFO("Enemy GameObject constructed with components: Transform, SpriteRenderer, Input, SpriteDirection, Follow, Rigidbody, Collider");
	}
}
