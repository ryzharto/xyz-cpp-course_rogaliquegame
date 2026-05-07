#include "pch.h"
#include "InputComponent.h"
#include "RenderSystem.h"
//#include "UIManager.h"
#include "Logger.h"

namespace XYZEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::HandleEvent(const sf::Event& event)
	{
		// Keyboard inputs
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)
		{
			verticalAxis += 1.0f;
			//LOG_INFO("Move forward");
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			verticalAxis -= 1.0f;
			//LOG_INFO("Move backward");
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::D)
		{
			horizontalAxis += 1.0f;
			//LOG_INFO("Move right");
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
		{
			horizontalAxis -= 1.0f;
			//LOG_INFO("Move left");
		}

		// Reloading
		if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
			ReloadPressed = true;
	}

	void InputComponent::Update(float deltaTime)
	{
		//if (!UIManager::Instance().IsInputBlocked())
		//{
			// Movements
			//verticalAxis = 0.f;
			//horizontalAxis = 0.f;

			// Reloading
			ReloadPressed = false;;

			// Mouse inputs
			sf::RenderWindow& window = RenderSystem::Instance()->GetMainWindow();
			if (window.hasFocus())
			{
				sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
				mouseWorldPos = window.mapPixelToCoords(pixelPos);
				bool currentLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

				if (currentLeftButtonPressed && !mouseLeftButtonPressed)
				{
					LOG_INFO("Mouse left button just pressed");
				}
				mouseLeftButtonPressed = currentLeftButtonPressed;
			}

		//}
	}

	void InputComponent::Render()
	{
	}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}

	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}
}

