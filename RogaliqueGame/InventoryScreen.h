#pragma once
#include "UIScreen.h"
#include "Item.h"
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
        bool IsWeaponEquipped(const Item& item) const;

    private:
        XYZEngine::GameObject* player = nullptr;
        sf::Font font;
        sf::Text title;
        std::vector<sf::Text> itemTexts; // list of item names
        std::vector<sf::Sprite> itemIcons; // list of items icons
        int selectedIndex = 0; // selected item
        std::vector<sf::Text> actionTexts; // list of available item actions
        int selectedActionIndex = 0; // selected action
        std::vector<ItemActionType> actionTypes;
        sf::RectangleShape background;
        sf::RectangleShape itemSelector; // подсветка выбранного предмета
        sf::RectangleShape actionSelector; // подсветка выбранного действия

        void RefreshItemList();
        void RefreshActionsForCurrentItem();
        void UpdateSelectorPosition();
        void UpdateActionSelectorPosition();
    };
}

