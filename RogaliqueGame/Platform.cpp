#include "Platform.h"
#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include <algorithm>
//#include "Debug.h"

namespace Ryzharto_ArcanoidGame
{
	// Функция инициализации игрока
	Platform::Platform(const sf::Vector2f& position) : GameObject(SETTINGS.RESOURCES_PATH + "platform.png", position, SETTINGS.PLATFORM_WIDTH, SETTINGS.PLATFORM_HEIGHT)
	{

	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * SETTINGS.PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(-timeDelta * SETTINGS.PLATFORM_SPEED);
		}
	}

	void Platform::Move(float speed)
	{
		auto position = sprite.getPosition();
		//position.x = position.x + speed;
		//position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		position.x = clamp(position.x + speed, SETTINGS.PLATFORM_WIDTH / 2.f, SETTINGS.SCREEN_WIDTH - SETTINGS.PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);

		if (!ball) return false;

		auto sqr = [](float x)
			{
			return x * x;
			};

		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->GetPosition();
		if (ballPos.x < rect.left)
		{
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0);
		}

		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0);
		}

		return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.0;
	}

	bool Platform::CheckCollision(std::shared_ptr<ICollidable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);

		if (!ball) return false;

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosInPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosInPlatform);
			return true;
		}

		return false;
	}
}