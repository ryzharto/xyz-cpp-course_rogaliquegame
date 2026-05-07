#pragma once
#include "Component.h"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace XYZEngine
{
	class InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void HandleEvent(const sf::Event& event);

		void Update(float deltaTime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;

		sf::Vector2f GetMouseWorldPosition() const { return mouseWorldPos; }
		bool IsMouseLeftButtonPressed() const { return mouseLeftButtonPressed; }
		bool IsReloadButtonPressed() const { return ReloadPressed; }

	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
		sf::Vector2f mouseWorldPos;
		bool mouseLeftButtonPressed = false;
		bool ReloadPressed = false;
	};
}


