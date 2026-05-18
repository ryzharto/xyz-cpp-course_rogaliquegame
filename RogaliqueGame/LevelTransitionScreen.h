#pragma once
#include <UIScreen.h>
#include <SFML/Graphics.hpp>

namespace Ryzharto_RogaliqueGame
{
    class LevelTransitionScreen : public XYZEngine::UIScreen
    {
    public:
        LevelTransitionScreen(const std::string& levelName, const std::string& description);
        void Init() override;
        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

    private:
        sf::Font font;
        sf::Text nameText;
        sf::Text descText;
        sf::RectangleShape background;
        float timer = 2.0f;
    };
}