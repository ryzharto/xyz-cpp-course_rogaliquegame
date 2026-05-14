#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Ryzharto_RogaliqueGame
{
	class GameOverMenu : public XYZEngine::UIScreen
	{
	public:
		GameOverMenu();
		void Init() override;
		void Draw(sf::RenderWindow& window) override;
		void HandleEvent(const sf::Event& event) override;

	private:
		sf::Font font;
		sf::Text title;
		std::vector<sf::Text> items; // list of item names
		int selectedIndex = 0; // selected item
		sf::RectangleShape background;
		sf::RectangleShape itemSelector; // подсветка выбранного предмета
		sf::RectangleShape actionSelector; // подсветка выбранного действия

		void UpdateSelectorPosition();
	};
}


