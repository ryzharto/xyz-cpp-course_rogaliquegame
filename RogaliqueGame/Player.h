#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"

namespace Ryzharto_RogaliqueGame
{
	class Player
	{
	public:
		Player();
		XYZEngine::GameObject* GetGameObject();

	private:
		XYZEngine::GameObject* gameObject;
	};
}