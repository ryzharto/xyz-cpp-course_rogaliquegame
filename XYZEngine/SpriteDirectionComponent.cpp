#include "pch.h"
#include "SpriteDirectionComponent.h"

namespace XYZEngine
{
	SpriteDirectionComponent::SpriteDirectionComponent(GameObject* gameObject) : Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		sprite = gameObject->GetComponent<SpriteComponent>();

		if (!input || !sprite)
		{
			LOG_WARN("'SpriteDirectionComponent' requires 'InputComponent' and 'SpriteComponent' which is missing. Removing component from GameObject '" + gameObject->GetName() + "'");
			gameObject->RemoveComponent(this);
			return;
		}
	}

	void SpriteDirectionComponent::Update(float deltaTime)
	{
		if (input->GetHorizontalAxis() < 0)
		{
			sprite->FlipX(true);
		}
		if (input->GetHorizontalAxis() > 0)
		{
			sprite->FlipX(false);
		}
	}

	void SpriteDirectionComponent::Render()
	{
	}
}