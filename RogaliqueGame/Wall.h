#include <GameWorld.h>
#include <ResourceSystem.h>
#include "GameObject.h"

namespace Ryzharto_RogaliqueGame
{
	class Wall
	{
	public:
		Wall(const XYZEngine::Vector2Df position, int textureMapIndex);
	private:
		XYZEngine::GameObject* gameObject;
	};
}