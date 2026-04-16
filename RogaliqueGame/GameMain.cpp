// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)
// Modified and extended by Ryzharto (ryzharto@yandex.ru)

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

//#include "Debug.h"

using namespace Ryzharto_RogaliqueGame;

int main()
{
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Ryzharto's Rogalique"));

	XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}

