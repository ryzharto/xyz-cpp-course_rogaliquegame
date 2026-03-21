#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ICollidable.h"
#include "IObserver.h"

namespace Ryzharto_ArcanoidGame 
{
	class Ball final : public GameObject, public ICollidable, public IObservable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		bool GetCollision(std::shared_ptr<ICollidable> collidable) const override;
		void ChangeAngle(float x);
		void Restart() override;

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90;
	};
}