#include "LevelTransitionScreen.h"
#include "UIManager.h"
#include "GameSettings.h"

namespace Ryzharto_RogaliqueGame
{
    LevelTransitionScreen::LevelTransitionScreen(const std::string& levelName, const std::string& description)
    {
        SetModal(true);
        nameText.setString(levelName);
        descText.setString(description);
    }

    void LevelTransitionScreen::Init()
    {
        if (!font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"))
        {
            // ошибка
            return;
        }
        nameText.setFont(font);
        nameText.setCharacterSize(48);
        nameText.setFillColor(sf::Color::White);
        descText.setFont(font);
        descText.setCharacterSize(24);
        descText.setFillColor(sf::Color::Yellow);
    }

    void LevelTransitionScreen::Update(float deltaTime)
    {
        timer -= deltaTime;
        if (timer <= 0.f)
        {
            // Закрываем экран
            Close();
        }
    }

    void LevelTransitionScreen::Draw(sf::RenderWindow& window)
    {
        sf::Vector2u winSize = window.getSize();
        background.setSize(sf::Vector2f(winSize));
        background.setFillColor(sf::Color::Black);
        window.draw(background);

        // Центрируем текст
        sf::FloatRect nameBounds = nameText.getLocalBounds();
        nameText.setOrigin(nameBounds.left + nameBounds.width / 2.f, nameBounds.top + nameBounds.height / 2.f);
        nameText.setPosition(winSize.x / 2.f, winSize.y / 2.f - 50.f);
        window.draw(nameText);

        sf::FloatRect descBounds = descText.getLocalBounds();
        descText.setOrigin(descBounds.left + descBounds.width / 2.f, descBounds.top + descBounds.height / 2.f);
        descText.setPosition(winSize.x / 2.f, winSize.y / 2.f + 30.f);
        window.draw(descText);   
    }

    void LevelTransitionScreen::HandleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            // Позволяем пропустить экран по нажатию Enter или Escape
            XYZEngine::UIManager::Instance()->RequestPop();
        }
    }
}