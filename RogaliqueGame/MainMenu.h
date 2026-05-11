#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace Ryzharto_RogaliqueGame
{
    class MainMenu : public XYZEngine::UIScreen
    {
    public:
        MainMenu();
        void Init() override;
        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

    private:
        sf::Font font;
        sf::Text title;
        std::vector<sf::Text> items;
        int selectedIndex = 0;
        sf::RectangleShape background;
        sf::RectangleShape selector;

        void UpdateSelectorPosition();
    };
}