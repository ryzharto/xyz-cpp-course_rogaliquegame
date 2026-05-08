#pragma once
#include <SFML/Graphics.hpp>

namespace XYZEngine
{
	class UIElement
	{
	public: 
		virtual ~UIElement() = default;
		virtual void Update(float deltaTime) {}
		virtual void Draw(sf::RenderWindow& window) = 0;
		virtual void HandleEvent(const sf::Event& event) {};

		void SetPosition(const sf::Vector2f& pos) { position = pos; }
		const sf::Vector2f& GetPosition() const { return position; }
		void SetView(const sf::Vector2f size) { viewSize = size; }
		const sf::Vector2f& GetSize() const { return viewSize; }
		sf::FloatRect GetGlobalBounds() const { return sf::FloatRect(position, viewSize); }

	protected:
		sf::Vector2f position;
		sf::Vector2f viewSize;
	};
}

