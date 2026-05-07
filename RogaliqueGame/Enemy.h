#pragma once
#include "GameObject.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
	// Base Enemy class
	class Enemy
	{
	public:
		Enemy(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* targetToFollow);
		virtual ~Enemy() = default;

		XYZEngine::GameObject* GetGameObject() const { return gameObject; }

	protected:
		XYZEngine::GameObject* gameObject = nullptr;
	};

}


