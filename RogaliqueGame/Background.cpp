#include "Background.h"
#include "Sprite.h"
#include "GameSettings.h"
#include <assert.h>

namespace Ryzharto_ArcanoidGame
{
	// Функция инициализации игрока
	Background::Background(const sf::Vector2f position) : GameObject(SETTINGS.RESOURCES_PATH + "grass_3.jpg", position, SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT)
	{
		sprite.setPosition({ SETTINGS.SCREEN_WIDTH / 2.f , SETTINGS.SCREEN_HEIGHT / 2.f });
	}
}