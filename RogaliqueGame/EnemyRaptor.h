#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include "GameWorld.h"

namespace Ryzharto_RogaliqueGame
{
	class EnemyRaptor : public Enemy
	{
	public:
		EnemyRaptor(const XYZEngine::Vector2Df& position, XYZEngine::GameObject* targetToFollow);
	};
}


