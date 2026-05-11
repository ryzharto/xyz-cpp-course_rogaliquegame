#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"

namespace XYZEngine
{
	class InputManager
	{
    public:
        static InputManager& Instance();

        void HandleEvents(const sf::Event& event);   // call in Engine::Run per frame
        void UpdateAxes();

        // Movement axis
        float GetHorizontalAxis() const { return horizontalAxis; }
        float GetVerticalAxis() const { return verticalAxis; }

        // Mouse input
        bool IsMouseLeftButtonPressed() const { return mouseLeftButtonPressed; }
        sf::Vector2f GetMouseWorldPosition() const { return mouseWorldPos; }

        // Buttons
        bool IsReloadButtonPressed() const { return reloadButtonPressed; }
        bool IsInteractButtonPressed() const { return interactButtonPressed; }
        bool ConsumeInteractPress();
        
        // Reset one frame dyration flags (call at end of frame)
        void ResetFrameFlags();

    private:
        InputManager() = default;

        // current values
        float horizontalAxis = 0.f;
        float verticalAxis = 0.f;
        sf::Vector2f mouseWorldPos;

        // Button states
        bool mouseLeftButtonPressed = false;
        bool reloadButtonPressed = false;
        bool interactButtonPressed = false;
        
        sf::RenderWindow* window = nullptr;
	};
}

