#pragma once
#include "UIElement.h"
#include <vector>
#include <memory>

namespace XYZEngine
{
    class UIScreen : public UIElement
    {
    public:
        virtual void Init() {}

        void Update(float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        void HandleEvent(const sf::Event& event) override;

        void AddChild(std::shared_ptr<UIElement> child);
        void RemoveChild(std::shared_ptr<UIElement> child);

        bool IsModal() const { return isModal; }
        void SetModal(bool modal) { isModal = modal; }

        void Close() { pendingClose = true; }
        bool IsClosing() const { return pendingClose;  }

    protected:
        std::vector<std::shared_ptr<UIElement>> children;
        bool isModal = false;
        bool pendingClose = false;
    };
}

