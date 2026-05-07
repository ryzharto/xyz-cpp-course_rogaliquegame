#pragma once
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteComponent.h"

namespace XYZEngine
{
	class SpriteDirectionComponent : public Component
	{
	public:
		SpriteDirectionComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;
	private:
		InputManager& input = InputManager::Instance();
		SpriteComponent* sprite;
	};
}

