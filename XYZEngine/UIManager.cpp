#include "pch.h"
#include "UIManager.h"
#include "../RogaliqueGame/PauseMenu.h"

namespace XYZEngine
{
	UIManager* UIManager::Instance()
	{
		static UIManager instance;
		return &instance;
	}

	void UIManager::PushScreen(std::shared_ptr<UIScreen> screen)
	{
		for (auto& s : screens)
			if (s == screen) return;

		screen->Init();
		screens.push_back(screen);
		LOG_INFO("UIManager::PushScreen: screen pushed, total screens: " + std::to_string(screens.size()));
	}

	void UIManager::PopScreen()
	{
		if (!screens.empty())
		{
			screens.pop_back();
			LOG_INFO("UIManager::PopScreen: screen deleted, total screens: " + std::to_string(screens.size()));
		}

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
		ProcessPendingClosures();
	}

	void UIManager::Draw(sf::RenderWindow& window)
	{	
		sf::View oldView = window.getView(); // Save current view (camera)
		window.setView(window.getDefaultView()); // Set default view (screen space)

		// Draw all screens
		for (auto& screen : screens)
			screen->Draw(window);

		window.setView(oldView); // Reset view from game camera
	}

	void UIManager::HandleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		{
			if (!IsInputBlocked())
			{
				// No modal screens - open pausemenu
				PushScreen(std::make_shared<Ryzharto_RogaliqueGame::PauseMenu>());
				return;
			}
		}

		// Transfer events to screens, but dont delete it now
		for (auto it = screens.rbegin(); it != screens.rend(); ++it)
		{
			(*it)->HandleEvent(event);
			if((*it)->IsModal())
				break;
		}
		// After events handled safely delete marked
		ProcessPendingClosures();
	}

	void UIManager::CloseActiveModal()
	{
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

	void UIManager::ProcessPendingClosures()
	{
		// Collect screens to close
		pendingRemove.clear();
		for (auto& screen : screens)
			if (screen->IsClosing())
				pendingRemove.push_back(screen);

		// Delete them from stack
		for (auto& screen : pendingRemove)
		{
			auto it = std::find(screens.begin(), screens.end(), screen);
			if (it != screens.end())
				screens.erase(it);
		}
	}
}