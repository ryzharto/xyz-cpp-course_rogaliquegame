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
		void CloseActiveModal();
		void RequestPop();
		void ClearAllScreens() { screens.clear(); }

		bool IsInputBlocked() const;
		bool IsEventConsumed() const { return eventConsumed; }

	private:
		UIManager() = default;
		void ProcessPendingClosures();

		std::vector<std::shared_ptr<UIScreen>> screens;
		std::vector<std::shared_ptr<UIScreen>> pendingRemove;
		bool pendingPop = false;
		bool eventConsumed = false;
	};
}

