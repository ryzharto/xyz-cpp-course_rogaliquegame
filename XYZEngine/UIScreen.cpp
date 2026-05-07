#include "pch.h"
#include "UIScreen.h"

namespace XYZEngine
{
	void UIScreen::Update(float deltaTime)
	{
		for (auto& child : children)
			child->Update(deltaTime);
	}

	void UIScreen::Draw(sf::RenderWindow& window)
	{
		for (auto& child : children)
			child->Draw(window);
	}

	bool UIScreen::HandleEvent(const sf::Event& event)
	{
		for (auto& child : children)
		{
			if (child->HandleEvent(event))
				return true;
		}
		return false;
	}

	void UIScreen::AddChild(std::shared_ptr<UIElement> child)
	{
		children.push_back(child);
	}

	void UIScreen::RemoveChild(std::shared_ptr<UIElement> child)
	{
		auto it = std::find(children.begin(), children.end(), child);
		if (it != children.end())
			children.erase(it);
	}
}