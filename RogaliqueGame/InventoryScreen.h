#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>
#include <vector>

namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
    class InventoryScreen : public XYZEngine::UIScreen
    {
    public:
        explicit InventoryScreen(XYZEngine::GameObject* player);
        void Init() override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

    private:
        XYZEngine::GameObject* player = nullptr;
        sf::Font font;
        sf::Text title;
        std::vector<sf::Text> itemTexts; // list of item names
        int selectedIndex = 0; // selected item
        std::vector<sf::Text> actionTexts; // list of available item actions
        int selectedActionIndex = 0; // selected action
        sf::RectangleShape background;
        sf::RectangleShape selector;

        void RefreshItemList();
        void UpdateSelectorPosition();
        void UpdateActionSelectorPosition();
    };
}

