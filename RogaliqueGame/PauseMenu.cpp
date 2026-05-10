#include "PauseMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "GameSettings.h"
#include "Logger.h"
#include <iostream>


namespace Ryzharto_RogaliqueGame
{
	PauseMenu::PauseMenu()
	{
		SetModal(true); // will block game inputs
	}

	void PauseMenu::Init()
	{
		if (!font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"))
		{
			XYZEngine::LOG_ERROR("Failed to load font for PauseMenu");
			return;
		}

        // Заголовок
        title.setFont(font);
        title.setString("PAUSE");
        title.setCharacterSize(48);
        title.setFillColor(sf::Color::Red);
        title.setStyle(sf::Text::Bold);
        title.setPosition(200, 100);

        // Пункты меню
        auto createItem = [&](const std::string& text, unsigned fontSize, float x, float y)
            {
            sf::Text t;
            t.setFont(font);
            t.setString(text);
            t.setCharacterSize(fontSize);
            t.setFillColor(sf::Color::White);
            t.setPosition(x, y);
            return t;
            };

        items.push_back(createItem("Resume", 30, 300, 250));
        items.push_back(createItem("Exit to Main Menu", 30, 300, 320));

        // Selection highlight 
        selector.setSize(sf::Vector2f(250, 40));
        selector.setFillColor(sf::Color(255, 255, 0, 80));   // semitransparent yellow
        selector.setPosition(items[0].getPosition().x - 10, items[0].getPosition().y - 5);
        selectedIndex = 0;

        // Полупрозрачный фон
        background.setSize(sf::Vector2f(1280, 720));
        background.setFillColor(sf::Color(0, 0, 0, 180));
	}

	void PauseMenu::Update(float deltaTime)
	{
	}

	void PauseMenu::Draw(sf::RenderWindow& window)
	{
        sf::Vector2u winSize = window.getSize();
        background.setSize(sf::Vector2f(winSize));
        window.draw(background);

        // Set title to center position
        sf::FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
        title.setPosition(winSize.x / 2.f, 120.f);
        window.draw(title);

        // Draw selector
        window.draw(selector);

        // Draw rest items
        for (auto& item : items)
            window.draw(item);
	}

    void PauseMenu::HandleEvent(const sf::Event& event)
	{
        if (event.type != sf::Event::KeyPressed)
            return;

        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            selectedIndex = (selectedIndex - 1 + static_cast<int>(items.size())) % items.size();
            UpdateSelectorPosition();
        }
        if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            selectedIndex = (selectedIndex + 1) % items.size();
            UpdateSelectorPosition();
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
            if (selectedIndex == 0 || selectedIndex == 1)
                Close(); // Close pause menu
        }
        if (event.key.code == sf::Keyboard::Escape)
        {
            Close();
        }
	}

	void PauseMenu::UpdateSelectorPosition()
	{
        if (selectedIndex >= 0 && selectedIndex < static_cast<int>(items.size()))
        {
            sf::Vector2f pos = items[selectedIndex].getPosition();
            selector.setPosition(pos.x - 10, pos.y - 5); // little offset to left and down
        }
	}

}