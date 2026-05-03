#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
	class Player
	{
	public:
		Player(const XYZEngine::Vector2Df& position);
		XYZEngine::GameObject* GetGameObject();

	private:
		XYZEngine::GameObject* gameObject;
	};
}