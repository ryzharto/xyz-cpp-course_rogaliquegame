#include "Player.h"
#include "ResourceSystem.h"
#include <SpriteColliderComponent.h>
#include <MovementComponent.h>
#include <SpriteDirectionComponent.h>
#include <SpriteMovementAnimationComponent.h>
#include <StatsComponent.h>
#include <AttackComponent.h>

namespace Ryzharto_RogaliqueGame
{
	Player::Player(const XYZEngine::Vector2Df& position)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("player")); // GetTextureMapElementShared("player",0))
		playerRenderer->SetPixelSize(100, 100);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto movement = gameObject->AddComponent<XYZEngine::MovementComponent>();
		movement->SetSpeed(400.f);

		auto spriteDirection = gameObject->AddComponent<XYZEngine::SpriteDirectionComponent>();

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(false);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		//auto animator = gameObject->AddComponent<XYZEngine::SpriteMovementAnimationComponent>();
		//animator->Initialize("player", 6.f);

		auto playerStats = gameObject->AddComponent<XYZEngine::StatsComponent>();
		playerStats->SetHealth(100.f);
		playerStats->SetArmour(100.f);

		auto attack = gameObject->AddComponent<XYZEngine::AttackComponent>();
		attack->SetAttackPower(15.f);
		attack->SetAttackRange(5.f);
		attack->SetAttackCooldown(0.7f);

		XYZEngine::LOG_INFO("Player GameObject constructed with components: Transform, SpriteRenderer, Camera, Input, Movement, Rigidbody, Collider, Stats");
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}