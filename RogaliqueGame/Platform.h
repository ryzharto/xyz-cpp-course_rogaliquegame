#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ICollidable.h"

namespace Ryzharto_ArcanoidGame 
{
	class Ball;

	// Player data
	class Platform : public GameObject, public ICollidable
	{
	public:
		Platform(const sf::Vector2f& position);
		void Update(float timeDelta) override;
		
		bool GetCollision(std::shared_ptr<ICollidable> collidable) const override;
		void OnHit() override {}

		bool CheckCollision(std::shared_ptr<ICollidable> collidable) override;

	private:
		void Move(float speed);
	};
}