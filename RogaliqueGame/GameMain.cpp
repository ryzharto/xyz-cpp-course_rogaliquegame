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

	ResourceSystem::Instance()->LoadTexture("player", "Resources/Textures/vecteezy_soldier-in-uniform-cartoon.png");
	ResourceSystem::Instance()->LoadTexture("Raptor_biege", "Resources/Textures/velociraptor-dinosaur-beige.png");
	ResourceSystem::Instance()->LoadTexture("Raptor_red", "Resources/Textures/velociraptor-dinosaur-red.png");
	ResourceSystem::Instance()->LoadTexture("Brachiosaurus", "Resources/Textures/brachiosaurus.png");
	ResourceSystem::Instance()->LoadTexture("Pteranodon", "Resources/Textures/pteranodon-dinosaur.png");

	ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 4, false);
	ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);

	ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/level-1.wav");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}

