#pragma once
#include "GameWorld.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
	class AI
	{
	public:
		AI(const XYZEngine::Vector2Df& posiiton, XYZEngine::GameObject* player);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}


