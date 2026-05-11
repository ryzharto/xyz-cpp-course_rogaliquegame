#include "pch.h"
#include "SpriteDirectionComponent.h"

namespace XYZEngine
{
	SpriteDirectionComponent::SpriteDirectionComponent(GameObject* gameObject) : Component(gameObject)
	{
		sprite = gameObject->GetComponent<SpriteComponent>();
	}

	void SpriteDirectionComponent::Update(float deltaTime)
	{
		auto* transform = gameObject->GetComponent<TransformComponent>();
		if (!transform) return;

		// Получаем мировую позицию мыши и текущую позицию объекта
		sf::Vector2f mouseWorld = input.GetMouseWorldPosition();
		Vector2Df myPos = transform->GetWorldPosition();

		// Если курсор левее персонажа – отражаем спрайт по X
		if (mouseWorld.x < myPos.x)
			sprite->FlipX(true);
		else
			sprite->FlipX(false);
	}

	void SpriteDirectionComponent::Render()
	{
	}
}