#include "PauseMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameSettings.h"
#include <iostream>

namespace Ryzharto_RogaliqueGame
{
	PauseMenu::PauseMenu()
	{
		SetModal(true); // will block game inputs
	}

	void PauseMenu::Init()
	{
	}

	void PauseMenu::Update(float deltaTime)
	{
	}

	void PauseMenu::Draw(sf::RenderWindow& window)
	{
	}

	void PauseMenu::HandleEvent(const sf::Event* event)
	{
	}

	void PauseMenu::UpdateSelectorPosition()
	{
	}

}