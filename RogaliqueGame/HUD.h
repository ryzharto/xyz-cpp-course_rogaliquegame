#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace XYZEngine
{
    class GameObject;
}

namespace Ryzharto_RogaliqueGame
{
    class HUD : public XYZEngine::UIScreen
    {
    public:
        explicit HUD(XYZEngine::GameObject* player);
        void Init() override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

    private:
        XYZEngine::GameObject* player = nullptr;

        // Graphics elements
        sf::Font font;

        // Texts
        sf::Text healthText;
        sf::Text staminaText;
        sf::Text armourText;
        sf::Text ammoText;

        // Health and stamina bars
        sf::RectangleShape healthBarBg; // background
        sf::RectangleShape healthBarFill;
        sf::RectangleShape staminaBarBg;
        sf::RectangleShape staminaBarFill;
        sf::RectangleShape armourBarBg;
        sf::RectangleShape armourBarFill;
        sf::Vector2f barSize = { 150,14 };

        // Weapon
        sf::Sprite weaponIcon;
        sf::Texture weaponIconTexture;
        sf::Vector2f iconSize = { 150, 50 };

        float margin = 20.f; // Margin betwee elements
    };
}

