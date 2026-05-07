#include "pch.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "UIManager.h"

namespace XYZEngine
{
	InputManager& InputManager::Instance()
	{
		static InputManager instance;
		return instance;
	}

	void InputManager::HandleEvents(const sf::Event& event)
	{
		// Instant events (fronts)
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::R)
				reloadButtonPressed = true;
			else if (event.key.code == sf::Keyboard::I || event.key.code == sf::Keyboard::Tab)
				inventoryButtonPressed = true;
			else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::P || event.key.code == sf::Keyboard::Pause)
				pauseButtonPressed = true;
			// Add here more keys if needed
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				mouseLeftButtonPressed = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
				mouseLeftButtonPressed = false;
			break;

		default:
			break;
		}
	}

	// Handles axes events
	void InputManager::UpdateAxes()
	{	
		if (!window)
			window = &RenderSystem::Instance()->GetMainWindow();

		if (window->hasFocus())
		{
			if (window)
			{
				// Update mouse world position
				sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
				mouseWorldPos = window->mapPixelToCoords(pixelPos);

				bool currentLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

				if (currentLeftButtonPressed && !mouseLeftButtonPressed)
				{
					//LOG_INFO("Input Manager::UpdateAxes: Mouse left button just pressed");
				}
				mouseLeftButtonPressed = currentLeftButtonPressed;
			}
		}

		// If UI blocked input - axes are zero
		if (UIManager::Instance()->IsInputBlocked())
		{
			horizontalAxis = 0.f;
			verticalAxis = 0.f;
			return;
		}

		// Keyboard axes handle
		horizontalAxis = 0.f;
		verticalAxis = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) horizontalAxis -= 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) horizontalAxis += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) verticalAxis += 1.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) verticalAxis -= 1.f;
	}

	void InputManager::ResetFrameFlags()
	{
		mouseLeftButtonPressed = false;
		reloadButtonPressed = false;
		inventoryButtonPressed = false;
	}


}