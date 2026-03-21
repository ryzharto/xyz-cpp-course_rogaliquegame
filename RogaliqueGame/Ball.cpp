#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>

namespace Ryzharto_ArcanoidGame
{
	Ball::Ball(const sf::Vector2f& position) : GameObject(SETTINGS.RESOURCES_PATH + "ball.png", position, SETTINGS.BALL_SIZE, SETTINGS.BALL_SIZE)
	{
		const float angle = 45.f + rand() % 90; // [45, 135] degree
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + SETTINGS.BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.x + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_WIDTH)
		{
			direction.x *= -1;
		}

		if (pos.y - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.y + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_HEIGHT)
		{
			direction.y *= -1;
		}
		Emit();
	}

	void Ball::InvertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction.y *= -1;
	}

	bool Ball::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Ball::OnHit()
	{
		lastAngle += std::rand() % 11 - 5; // rand() % 11 даёт 0..10, вычитаем 5 → -5..5
		ChangeAngle(lastAngle);
	}

	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		const auto pi = std::acos(-1.f);
		direction.x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		direction.y = -1 * abs(std::sin(pi / 180.f * angle));
	}

	void Ball::Restart()
	{
		GameObject::Restart();
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

}