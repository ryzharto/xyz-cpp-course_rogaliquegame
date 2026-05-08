#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>

namespace Ryzharto_RogaliqueGame
{
	class PauseMenu : public XYZEngine::UIScreen
	{
	public:
		PauseMenu();
		void Init() override;
		void Update(float deltaTime) override;
		void Draw(sf::RenderWindow& window) override;
		void HandleEvent(const sf::Event& event) override;

	private:
		sf::Font font;
		sf::Text title;
		std::vector<sf::Text> items; // Resume, Main Menu, etc...
		int selectedIndex = 0;

		// Background
		sf::RectangleShape background;
		sf::RectangleShape selector; // highlight of selected item

		void UpdateSelectorPosition();
	};
}

