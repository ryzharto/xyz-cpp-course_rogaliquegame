#include "InventoryScreen.h"
#include "GameObject.h"
#include "InventoryComponent.h"
#include "UIManager.h"
#include "GameSettings.h"
#include "WorldItem.h"
#include <sstream>

namespace Ryzharto_RogaliqueGame
{
	InventoryScreen::InventoryScreen(XYZEngine::GameObject* player) : player(player)
	{
		SetModal(true);
	}

	void InventoryScreen::Init()
	{
		if (!font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"))
		{
			XYZEngine::LOG_ERROR("InventoryScreen::Init: Failed to load font");
			return;
		}

		// Заголовок
		title.setFont(font);
		title.setString("INVENTORY");
		title.setCharacterSize(48);
		title.setFillColor(sf::Color::Red);
		title.setStyle(sf::Text::Bold);
		title.setPosition(200, 50);

		// Selection highlight 
		selector.setSize(sf::Vector2f(250, 40));
		selector.setFillColor(sf::Color(255, 255, 0, 80));   // semitransparent yellow

		// Полупрозрачный фон
		background.setFillColor(sf::Color(0, 0, 0, 180));
		RefreshItemList();
	}

	void InventoryScreen::Update(float deltaTime)
	{
		// Update item list if inventory was changed
	}

	void InventoryScreen::Draw(sf::RenderWindow& window)
	{
		sf::Vector2u winSize = window.getSize();
		background.setSize(sf::Vector2f(winSize));
		window.draw(background);

		// Set title to center position
		sf::FloatRect titleBounds = title.getLocalBounds();
		title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
		title.setPosition(winSize.x / 2.f, 120.f);
		window.draw(title);

		// Draw items
		for (auto& text : itemTexts)
			window.draw(text);

		// Draw item actions
		for (auto& text : actionTexts)
			window.draw(text);

		// Draw selector
		if (!itemTexts.empty())
			window.draw(selector);

		// Input hint
		sf::Text hint;
		hint.setFont(font);
		hint.setCharacterSize(18);
		hint.setFillColor(sf::Color(150,150,150));
		hint.setString("[Up/Down] for select Item   [Left/Right] for select Action   [E/Enter] for Use item   [Tab/I/Esc] for Close   [Q] for Drop");
		hint.setPosition(50.f, winSize.y - 40.f);
		window.draw(hint);
	}

	void InventoryScreen::HandleEvent(const sf::Event& event)
	{
		if (event.type != sf::Event::KeyPressed) return;

		int count = static_cast<int>(itemTexts.size());

		// Item selection
		if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
		{
			if (count == 0) return;
			selectedIndex = (selectedIndex - 1 + count) % count; // Move to last item
			UpdateSelectorPosition();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			if (count == 0) return;
			selectedIndex = (selectedIndex + 1) % count; // Move to next bottom item (under current)
			UpdateSelectorPosition();
		}

		// Item Action selection
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
		{
			if (actionTexts.size() > 1)
			{
				selectedActionIndex = (selectedActionIndex - 1 + count) % count; // Move to last item
				UpdateActionSelectorPosition();
			}
		}
		else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
		{
			if (actionTexts.size() > 1)
			{
				selectedActionIndex = (selectedActionIndex + 1) % count; // Move to next bottom item (under current)
				UpdateActionSelectorPosition();
			}
		}

		// Use item
		else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::E)
		{
			if (count == 0) return;
			auto inv = player->GetComponent<XYZEngine::InventoryComponent>();
			if (inv)
			{
				inv->UseItem(selectedIndex, selectedActionIndex, player);
				RefreshItemList();
				if (inv->GetItemCount() == 0) Close(); // Close inventory if its empty
			}
		}
		else if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Tab || event.key.code == sf::Keyboard::I)
		{
			Close();
		}

		// Drop item
		else if (event.key.code == sf::Keyboard::Q)   // Drop
		{
			if (!itemTexts.empty())
			{
				auto inv = player->GetComponent<XYZEngine::InventoryComponent>();
				if (inv && selectedIndex < inv->GetItemCount())
				{
					// Создаём WorldItem на позиции игрока
					auto playerTransform = player->GetComponent<XYZEngine::TransformComponent>();
					XYZEngine::Vector2Df dropPos = playerTransform->GetWorldPosition();
					const auto& item = inv->GetItem(selectedIndex);
					std::string texName = "Bullet";//item.name;
					new Ryzharto_RogaliqueGame::WorldItem(dropPos, item, texName);
					inv->RemoveItem(selectedIndex);
					RefreshItemList();
					if (inv->GetItemCount() == 0) Close();
				}
			}
		}
	}

	void InventoryScreen::RefreshItemList()
	{
		// Fill items
		itemTexts.clear();
		auto inv = player->GetComponent<XYZEngine::InventoryComponent>();
		if (!inv) return;

		for (size_t i = 0; i < inv->GetItemCount(); ++i)
		{
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setString(inv->GetItem(i).name);
			text.setPosition(300.f, 150.f + i * 35.f); // offset
			itemTexts.push_back(text);
		}

		if (!itemTexts.empty())
		{
			selectedIndex = 0;
			UpdateSelectorPosition();
		}

		// Fill available actions list
		actionTexts.clear();
		if (selectedIndex >= 0 && selectedIndex < inv->GetItemCount())
		{
			const auto& actions = inv->GetItem(selectedIndex).actions;

			for (size_t i = 0; i < actions.size(); ++i)
			{
				sf::Text text;
				text.setFont(font);
				text.setCharacterSize(20);
				text.setFillColor(sf::Color::White);
				text.setString(actions[i].name);
				text.setPosition(650.f, 150.f + i * 30.f); // offset
				actionTexts.push_back(text);
			}
			if (!actionTexts.empty())
				selectedActionIndex = 0;
			UpdateActionSelectorPosition();
		}
	}

	void InventoryScreen::UpdateSelectorPosition()
	{
		if (selectedIndex >= 0 && selectedIndex < static_cast<int>(itemTexts.size()))
		{
			sf::Vector2f pos = itemTexts[selectedIndex].getPosition();
			selector.setPosition(pos.x - 10.f, pos.y - 5);
		}
	}

	void InventoryScreen::UpdateActionSelectorPosition()
	{
		if (selectedActionIndex < static_cast<int>(actionTexts.size()))
		{
			sf::Vector2f pos = actionTexts[selectedActionIndex].getPosition();
			selector.setPosition(pos.x - 5.f, pos.y - 2);
			selector.setSize(sf::Vector2f(100, 24));
		}
	}
}