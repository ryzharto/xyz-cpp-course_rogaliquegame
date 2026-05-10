#pragma once
#include "UIScreen.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace XYZEngine
{
    class GameObject;
}

namespace Ryzharto_RogaliqueGame
{
    struct Notification
    {
        std::string text;
        float lifetime = -1.f; // negative - permanent
        float age = 0.f;
    };

    class HUD : public XYZEngine::UIScreen
    {
    public:
        explicit HUD(XYZEngine::GameObject* player);
        void Init() override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;

        void ShowNotification(const std::string& text, float lifetime = -1.f);
        void ClearPersistentNotification();   // delete persistent notify
        void UpdateInteractableNotification();

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
        
        // Notifications
        std::vector<Notification> notifications;
        sf::Text notifyText;
    };
}

