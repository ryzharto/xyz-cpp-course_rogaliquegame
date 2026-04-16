#include "Player.h"
#include "ResourceSystem.h"
#include <SpriteColliderComponent.h>

namespace Ryzharto_RogaliqueGame
{
	Player::Player()
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject();
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->RotateBy(90.f);
		transform->MoveBy({ 1.f, 0.f });

		auto test = XYZEngine::GameWorld::Instance()->CreateGameObject();
		auto testTransform = test->GetComponent < XYZEngine::TransformComponent>();
		testTransform->SetParent(transform);

		transform->RotateBy(-90.f);
		transform->Print();
		testTransform->Print();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	XYZEngine::GameObject* Player::GetGameObject()
	{
		return gameObject;
	}
}