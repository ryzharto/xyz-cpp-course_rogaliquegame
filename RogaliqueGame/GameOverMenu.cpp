#include "GameOverMenu.h"
#include "Game.h"
#include "UIManager.h"
#include "GameSettings.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
	GameOverMenu::GameOverMenu()
	{
		SetModal(true);
	}

	void GameOverMenu::Init()
	{
		if (!font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"))
		{
			XYZEngine::LOG_ERROR("InventoryScreen::Init: Failed to load font");
			return;
		}

		// Header
		title.setFont(font);
		title.setString("YOU DIED");
		title.setCharacterSize(64);
		title.setFillColor(sf::Color::Red);
		title.setStyle(sf::Text::Bold);

		// Items
		auto createItem = [&](const std::string& text, float x, float y)
			{
				sf::Text t;
				t.setFont(font);
				t.setString(text);
				t.setCharacterSize(30);
				t.setFillColor(sf::Color::White);
				t.setPosition(x, y);
				return t;
			};
		items.push_back(createItem("Restart", 300, 300));
		items.push_back(createItem("Main Menu", 300, 370));

		// Selector highlight
		itemSelector.setSize(sf::Vector2f(250, 40));
		itemSelector.setFillColor(sf::Color(255, 255, 0, 80));
		itemSelector.setPosition(items[0].getPosition().x - 10, items[0].getPosition().y - 5);
		selectedIndex = 0;

		// Background
		background.setFillColor(sf::Color(0, 0, 0, 180));
	}

	void GameOverMenu::Draw(sf::RenderWindow& window)
	{
		sf::Vector2u winSize = window.getSize();
		background.setSize(sf::Vector2f(winSize));
		window.draw(background);

		// Set title to center
		sf::FloatRect bounds = title.getLocalBounds();
		title.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
		title.setPosition(winSize.x / 2.f, 100.f);
		window.draw(title);

		window.draw(itemSelector);
		for (auto& item : items)
			window.draw(item);
	}

	void GameOverMenu::HandleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed) return;

		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			selectedIndex = (selectedIndex - 1 + items.size()) % items.size();
			UpdateSelectorPosition();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			selectedIndex = (selectedIndex + 1) % items.size();
			UpdateSelectorPosition();
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
			if (selectedIndex == 0)       // New Game
			{
				Game::Instance().RequestNewGame();   // отложенный переход
			}
			else if (selectedIndex == 1)  // Quit
			{
				Game::Instance().RequestReturnToMainMenu();
			}
		}
		if (event.key.code == sf::Keyboard::Escape)
		{
			Game::Instance().RequestReturnToMainMenu();
		}
	}

	void GameOverMenu::UpdateSelectorPosition()
	{
		if (selectedIndex >= 0 && selectedIndex < static_cast<int>(items.size()))
		{
			sf::Vector2f pos = items[selectedIndex].getPosition();
			itemSelector.setPosition(pos.x - 10, pos.y - 5);
		}
	}
}