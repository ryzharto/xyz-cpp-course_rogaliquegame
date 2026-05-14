// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)
// Modified and extended by Ryzharto (ryzharto@yandex.ru)

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Engine.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "HUD.h"
#include "UIManager.h"
#include "PrefabSetup.h"
#include "Matrix2D.h"

//using namespace Ryzharto_RogaliqueGame;

int main()
{
	XYZEngine::Engine::Instance(); // Logger initialize

	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "Ryzharto's Creta Roguelite"));

	// Default texture
	XYZEngine::ResourceSystem::Instance()->LoadTexture("default_texture", "Resources/Textures/default_texture.png");

	// Actors - player and enemies
	XYZEngine::ResourceSystem::Instance()->LoadTexture("player", "Resources/Textures/vecteezy_soldier-in-uniform-cartoon.png");
	//XYZEngine::ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 4, false);
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Raptor_biege", "Resources/Textures/velociraptor-dinosaur-beige.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Raptor_red", "Resources/Textures/velociraptor-dinosaur-red.png");
	//XYZEngine::ResourceSystem::Instance()->LoadTexture("Brachiosaurus", "Resources/Textures/brachiosaurus.png");
	//XYZEngine::ResourceSystem::Instance()->LoadTexture("Pteranodon", "Resources/Textures/pteranodon-dinosaur.png");

	// Projectiiles
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Bullet", "Resources/Textures/bullet.png");

	// Items
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Medkit", "Resources/Textures/medkit.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Ammo_box", "Resources/Textures/ammobox.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Melee_Machete", "Resources/Textures/weapon_machete.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("SMG_PPK-20", "Resources/Textures/weapon_ppk-20.png");

	// Static objects
	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall.png", { 16, 16 }, 48, false);
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Terminal", "Resources/Textures/terminal.png");

	// Music
	XYZEngine::ResourceSystem::Instance()->LoadSound("music", "Resources/Sounds/level-1.wav");

	Ryzharto_RogaliqueGame::SetupPrefabs();

	Ryzharto_RogaliqueGame::Game::Instance().Init();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}

