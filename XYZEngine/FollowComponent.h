#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

namespace XYZEngine
{
	class FollowComponent : public Component
	{
	public:
		FollowComponent(GameObject* gameObject);
		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(GameObject* targetObject);
		void SetSpeed(float newSpeed);
		float GetSpeed() const;

	private:
		TransformComponent* transform = nullptr;
		TransformComponent* targetTransform = nullptr;
		SpriteComponent* spriteRenderer = nullptr;

		float speed = 100.f; // default speed
	};
}


