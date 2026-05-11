#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>

namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
    class InteractionMenu : public XYZEngine::UIScreen
    {
    public:
        InteractionMenu(XYZEngine::GameObject* interactable, XYZEngine::GameObject* instigator);
        void Init() override;
        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

    private:
        XYZEngine::GameObject* interactable;
        XYZEngine::GameObject* instigator;
        sf::Font font;
        std::vector<sf::Text> actionTexts;
        int selectedIndex = 0;
        sf::RectangleShape background;
        sf::RectangleShape selector;
    };
}