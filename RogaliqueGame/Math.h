#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace Ryzharto_ArcanoidGame
{
	sf::Vector2f GetSpriteScale(const sf::Sprite& sprite, const Vector2Df& desiredSize);
	sf::Vector2f GetItemOrigin(const sf::Sprite& sprite, const Vector2Df& relativePosition);
	sf::Vector2f GetItemOrigin(const sf::Text& text, const sf::Vector2f& relativePosition);

	template<typename T>
	bool IsPointInRect(const Vector2D<T>& point, const Vector2D<T>& rectTL, const Vector2D<T>& rectBR)
	{
		if (point.x < rectTL.x || point.x > rectBR.x)
		{
			return false;
		}
		if (point.y < rectTL.y || point.y > rectBR.y)
		{
			return false;
		}
		return true;
	}

	template<typename T>
	const T& clamp(const T& value, const T& low, const T& high)
	{
		if (value < low) return low;
		if (value > high) return high;
		return value;
	}

	/*
	// Объявляем структуру для координат
	struct Vector2D
	{
		float x = 0;
		float y = 0;
	};

	// Объявляем синоним для структуры Vector2D
	typedef Vector2D Position2D;

	// Генерация случайной позиции на экране (x,y)
	Position2D GetRandomPositionOnScreen(float screen_Widht, float screen_Height);

	// Проверка коллизии между квадратными объектами
	bool IsRectanglesCollide(Position2D rect1Position, Vector2D rect1Size, Position2D rect2Position, Vector2D rect2Size);

	// Проверка коллизии между круглыми объектами
	bool IsCircleCollide(Position2D circle1Position, float circle1Radius, Position2D circle2Position, float circle2Radius);

	// Функция масштабирования спрайта 
	void SetSpriteSize(sf::Sprite& sprite, float desiredWidht, float desiredHeight);

	// Функция смещения начала координат для спрайта
	void SetSpriteRelativeOrigin(sf::Sprite& sprite, float originX, float originY);
	*/
}

template<>
struct std::hash<Ryzharto_ArcanoidGame::Vector2Di>
{
	std::size_t operator()(const Ryzharto_ArcanoidGame::Vector2Di& v) const noexcept
	{
		return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
	}
};