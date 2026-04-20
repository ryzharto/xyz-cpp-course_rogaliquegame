#include "AI.h"
#include "ResourceSystem.h"
#include <SpriteColliderComponent.h>
#include "MovementComponent.h"
#include "SpriteDirectionComponent.h"
#include "SpriteRendererComponent.h"
#include <FollowComponent.h>

namespace Ryzharto_RogaliqueGame
{
	AI::AI(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("AI");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Raptor_biege"));
		renderer->SetPixelSize(200, 100);

		auto aiInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto spriteDirection = gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

		auto follower = gameObject->AddComponent<XYZEngine::FollowComponent>();
		follower->SetTarget(player);
		follower->SetSpeed(120.f);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* AI::GetGameObject()
	{
		return gameObject;
	}
}