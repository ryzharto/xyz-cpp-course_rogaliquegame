#include "pch.h"
#include "UIManager.h"

namespace XYZEngine
{
	UIManager* UIManager::Instance()
	{
		static UIManager instance;
		return &instance;
	}

	void UIManager::PushScreen(std::shared_ptr<UIScreen> screen)
	{
		screen->Init();
		screens.push_back(screen);
		LOG_INFO("UIManager::PushScreen: screen pushed, total screens: " + std::to_string(screens.size()));
	}

	void UIManager::PopScreen()
	{
		if (!screens.empty())
			screens.pop_back();
	}

	void UIManager::SetScreen(std::shared_ptr<UIScreen> screen)
	{
		screens.clear();
		PushScreen(screen);
	}

	void UIManager::Update(float deltaTime)
	{
		for (auto& screen : screens)
			screen->Update(deltaTime);
	}

	void UIManager::Draw(sf::RenderWindow& window)
	{
		// Save current view (camera)

		sf::View oldView = window.getView();
		// set default view (screen space)
		window.setView(window.getDefaultView());

		// Draw all screens
		for (auto& screen : screens)
			screen->Draw(window);

		// Reset view from game camera
		window.setView(oldView);
	}

	void UIManager::HandleEvent(const sf::Event& event)
	{
		for (auto it = screens.rbegin(); it != screens.rend(); ++it)
		{
			if ((*it)->HandleEvent(event))
				break;
			if((*it)->IsModal())
				break;
		}
	}

	bool UIManager::IsInputBlocked() const
	{
		for (auto it = screens.rbegin(); it != screens.rend(); ++it)
		{
			if ((*it)->IsModal())
				return true;
		}
		return false;
	}
}