#include "Math.h"
#include <cstdlib>
#include <SFML/Graphics.hpp>

namespace Ryzharto_ArcanoidGame
{
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize)
	{
		const sf::Vector2u textureSize = sprite.getTexture()->getSize();
		const sf::Vector2f spriteScale = { desiredSize.x / textureSize.x, desiredSize.y / textureSize.y };
		return spriteScale;
	}

	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition)
	{
		const sf::Vector2u textureSize = sprite.getTexture()->getSize();
		return { relativePosition.x * textureSize.x, relativePosition.y * textureSize.y };
	}

	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition)
	{
		sf::FloatRect textSize = text.getLocalBounds();
		return {
			(textSize.left + textSize.width) * relativePosition.x,
			(textSize.top + textSize.height) * relativePosition.y,
		};
	}

	/*
	// Генерация случайной позиции на экране (x,y)
	Position GetRandomPositionOnScreen(float screen_Widht, float screen_Height)
	{
		Position2D result;
		result.x = rand() / (float)RAND_MAX * screen_Widht; // случайная координата по X
		result.y = rand() / (float)RAND_MAX * screen_Height; // случайная координата по Y
		return result;
	}

	// Проверка коллизии между квадратными объектами
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size)
	{
		float dX = (float)fabs(rect1Position.x - rect2Position.x); // модуль 
		float dY = (float)fabs(rect1Position.y - rect2Position.y); // модуль 

		// Проверка коллизии с квадратными препятствиями
		return (dX <= (rect1Size.x + rect2Size.x) / 2.f &&
			dY <= (rect1Size.y + rect2Size.y) / 2.f);
	}

	// Проверка коллизии между круглыми объектами
	bool IsCircleCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius)
	{
		float squareDistance = (circle1Position.x - circle2Position.x) * (circle1Position.x - circle2Position.x) +
			(circle1Position.y - circle2Position.y) * (circle1Position.y - circle2Position.y); // Квадрат расстояния (квадрат половины суммы размеров)
		float squareRadiusSum = (circle1Radius + circle2Radius) * (circle1Radius + circle2Radius); // Сумма квадратов радиуса

		return (squareDistance <= squareRadiusSum); // Проверка условия
	}


	void SetSpriteSize(sf::Sprite& sprite, float desiredWidht, float desiredHeight)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds(); // Получаем кооринаты верхней левой точки спрайта и его размеры
		sf::Vector2f scale = { desiredWidht / spriteRect.width, desiredHeight / spriteRect.height };
		sprite.setScale(scale);
	}

	// Функция смещения начала координат для спрайта
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY)
	{
		sf::FloatRect spriteRect = sprite.getLocalBounds();
		sprite.setOrigin(spriteRect.width * originX, spriteRect.height * originY);
	}
	*/
}