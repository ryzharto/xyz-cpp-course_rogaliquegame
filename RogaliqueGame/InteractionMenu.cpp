#include "InteractionMenu.h"
#include "InteractableComponent.h"
#include "UIManager.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "GameSettings.h"
#include "Vector.h"

namespace Ryzharto_RogaliqueGame
{
    InteractionMenu::InteractionMenu(XYZEngine::GameObject* interactable, XYZEngine::GameObject* instigator) : interactable(interactable), instigator(instigator)
    {
        SetModal(true);
    }

    void InteractionMenu::Init()
    {
        font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf");

        auto comp = interactable->GetComponent<XYZEngine::InteractableComponent>();
        if (!comp) return;

        int i = 0;
        for (const auto& action : comp->GetActions())
        {
            sf::Text t;
            t.setFont(font);
            t.setCharacterSize(24);
            t.setFillColor(sf::Color::White);
            t.setString(action.name);
            XYZEngine::Vector2Df worldPos = interactable->GetComponent<XYZEngine::TransformComponent>()->GetWorldPosition();
            t.setPosition(worldPos.x, worldPos.y + i * 35.f);
            actionTexts.push_back(t);
            ++i;
        }

        selector.setSize(sf::Vector2f(150, 30));
        selector.setFillColor(sf::Color(255, 255, 0, 80));
        if (!actionTexts.empty())
            selector.setPosition(actionTexts[0].getPosition().x - 10, actionTexts[0].getPosition().y - 5);

        background.setFillColor(sf::Color(0, 0, 0, 200));
    }

    void InteractionMenu::Draw(sf::RenderWindow& window)
    {
        sf::Vector2u winSize = window.getSize();
        background.setSize(sf::Vector2f(winSize));
        window.draw(background);
        for (auto& t : actionTexts) window.draw(t);
        window.draw(selector);
    }

    void InteractionMenu::HandleEvent(const sf::Event& event)
    {
        if (event.type != sf::Event::KeyPressed) return;
        int count = static_cast<int>(actionTexts.size());

        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        {
            if (count == 0) return;
            selectedIndex = (selectedIndex - 1 + count) % count;
            selector.setPosition(actionTexts[selectedIndex].getPosition().x - 10, actionTexts[selectedIndex].getPosition().y - 5);
        }
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        {
            if (count == 0) return;
            selectedIndex = (selectedIndex + 1) % count;
            selector.setPosition(actionTexts[selectedIndex].getPosition().x - 10, actionTexts[selectedIndex].getPosition().y - 5);
        }
        else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::E)
        {
            auto comp = interactable->GetComponent<XYZEngine::InteractableComponent>();
            if (comp)
            {
                comp->ExecuteAction(selectedIndex, instigator);
                XYZEngine::LOG_INFO("InteractionMenu::HandleEvent: interaction");
                Close();
            }
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            Close();
        }
    }
}