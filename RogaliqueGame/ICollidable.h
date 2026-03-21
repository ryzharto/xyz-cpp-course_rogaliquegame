#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace Ryzharto_ArcanoidGame
{
	class ICollidable
	{
	protected:
		virtual void OnHit() = 0;
	public:
		virtual bool CheckCollision(std::shared_ptr<ICollidable> collidable)
		{
			if (GetCollision(collidable))
			{
				OnHit();
				collidable->OnHit();
				return true;
			}
			return false;
		}

		virtual bool GetCollision(std::shared_ptr<ICollidable> collidable) const = 0;
	};
}