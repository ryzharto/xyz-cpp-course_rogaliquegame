#pragma once
#include "UIScreen.h"
#include <vector>
#include <memory>

namespace XYZEngine
{
	class UIManager
	{
	public:
		static UIManager* Instance();

		void PushScreen(std::shared_ptr<UIScreen> screen);
		void PopScreen();
		void SetScreen(std::shared_ptr<UIScreen> screen);
		void Update(float deltaTime);
		void Draw(sf::RenderWindow& window);
		void HandleEvent(const sf::Event& event);

		bool IsInputBlocked() const;

	private:
		UIManager() = default;
		std::vector<std::shared_ptr<UIScreen>> screens;
	};
}

