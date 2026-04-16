// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)
// Modified and extended by Ryzharto (ryzharto@yandex.ru)

#include <SFML/Graphics.hpp>
#include "Application.h"
#include <Engine.h>

#include "Debug.h"

using namespace Ryzharto_RogaliqueGame;

int main()
{
	//Application::Instance().Run();
	Engine::Engine::Instance()->Run();

	return 0;
}

