#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace Ryzharto_ArcanoidGame
{
	class Background : public GameObject
	{
	public:
		Background(const sf::Vector2f position);
		~Background() = default;
	};
}