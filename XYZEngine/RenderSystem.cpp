#include "pch.h"
#include "RenderSystem.h"
#include <cassert>

namespace XYZEngine
{
	RenderSystem* RenderSystem::Instance()
	{
		static RenderSystem render;
		return &render;
	}

	void RenderSystem::SetMainWindow(sf::RenderWindow* newWindow)
	{
		if (!newWindow)
		{
			LOG_ERROR("RenderSystem::SetMainWindow called with null window pointer");
			assert(false);
		}

		window = newWindow;
	}

	sf::RenderWindow& RenderSystem::GetMainWindow() const
	{
		return *window;
	}

	void RenderSystem::Render(const sf::Drawable& drawable)
	{
		if (!window)
		{
			LOG_ERROR("RenderSystem::Render called but no window is set");
			assert(false);
			return;
		}

		window->draw(drawable);
	}
}