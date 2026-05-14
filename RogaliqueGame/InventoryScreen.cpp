#include "InventoryScreen.h"
#include "GameObject.h"
#include "ResourceSystem.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "UIManager.h"
#include "GameSettings.h"
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

		// Item selection highlight 
		itemSelector.setSize(sf::Vector2f(250, 40));
		itemSelector.setFillColor(sf::Color(255, 255, 0, 80));   // semitransparent yellow

		// Action selection highlight 
		actionSelector.setSize(sf::Vector2f(100, 24));
		actionSelector.setFillColor(sf::Color(100, 255, 100, 80)); // another color


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

		// Draw items icons
		for (auto& icon : itemIcons)
			window.draw(icon);

		// Draw items texts
		for (auto& text : itemTexts)
			window.draw(text);

		// Draw item actions
		for (auto& text : actionTexts)
			window.draw(text);

		// Draw selectors
		if (!itemTexts.empty())
			window.draw(itemSelector);
		if (!actionTexts.empty())
			window.draw(actionSelector);

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
			RefreshActionsForCurrentItem();
		}
		else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
		{
			if (count == 0) return;
			selectedIndex = (selectedIndex + 1) % count; // Move to next bottom item (under current)
			UpdateSelectorPosition();
			RefreshActionsForCurrentItem();
		}

		// Item Action selection
		if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
		{
			int actionCount = static_cast<int>(actionTexts.size());
			if (actionCount > 1)
			{
				selectedActionIndex = (selectedActionIndex - 1 + actionCount) % actionCount; // Move to last item 
				UpdateActionSelectorPosition();
			}
		}
		else if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
		{
			int actionCount = static_cast<int>(actionTexts.size());
			if (actionCount > 1)
			{
				selectedActionIndex = (selectedActionIndex + 1) % actionCount; // Move to next bottom item (under current)
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
				if (selectedActionIndex < 0 || selectedActionIndex >= static_cast<int>(actionTypes.size()))
					return;

				ItemActionType type = actionTypes[selectedActionIndex];

				inv->UseItem(selectedIndex, type, player);
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
					// Ищем действие "Drop" среди действий текущего предмета
					auto available = inv->GetItem(selectedIndex).GetAvailableActions(player);
					ItemActionType dropType = ItemActionType::None;
					for (const auto& a : available)
					{
						if (a.type == ItemActionType::Drop)
						{
							dropType = a.type;
							break;
						}
					}
					if (dropType != ItemActionType::None)
					{
						inv->UseItem(selectedIndex, dropType, player);
						RefreshItemList();
						if (inv->GetItemCount() == 0) Close();
					}
				}
			}
		}
	}

	bool InventoryScreen::IsWeaponEquipped(const Item& item) const
	{
		auto* weapon = player->GetComponent<XYZEngine::WeaponComponent>();
		if (!weapon) return false;
		return weapon->HasWeapon(item.GetPrefabKey());
	}

	void InventoryScreen::RefreshItemList()
	{
		// Clear actions and items lists
		itemTexts.clear();
		itemIcons.clear();

		auto inv = player->GetComponent<XYZEngine::InventoryComponent>();
		if (!inv) return;

		for (size_t i = 0; i < inv->GetItemCount(); ++i)
		{
			// Items Icons
			sf::Sprite icon;
			const auto& item = inv->GetItem(i);
			const sf::Texture* texture = XYZEngine::ResourceSystem::Instance()->GetTextureShared(inv->GetItem(i).GetIconTextureKey());
			if (texture == nullptr)
				texture = XYZEngine::ResourceSystem::Instance()->GetTextureShared("default_texture");
			else
			{
				icon.setTexture(*texture);
				sf::Vector2u textureSize = texture->getSize();
				float desiredHeight = 24.f;
				float scale = desiredHeight / textureSize.y; // scale only height
				icon.setScale(scale, scale);
				icon.setPosition(200.f, 150.f + i * 35.f);
			}
			itemIcons.push_back(icon);

			// Items names
			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(24);
			text.setFillColor(sf::Color::White);
			text.setString(inv->GetItem(i).GetName());
			text.setPosition(300.f, 150.f + i * 35.f); // offset
			itemTexts.push_back(text);
		}

		// Если selectedIndex выходит за границы – сбросить на 0
		if (selectedIndex >= inv->GetItemCount())
			selectedIndex = 0;

		if (!itemTexts.empty())
		{
			selectedIndex = 0;
			UpdateSelectorPosition();
		}

		RefreshActionsForCurrentItem();
	}

	void InventoryScreen::RefreshActionsForCurrentItem()
	{
		actionTexts.clear();
		actionTypes.clear();

		auto inv = player->GetComponent<XYZEngine::InventoryComponent>();
		if (!inv || selectedIndex >= inv->GetItemCount()) return;

		const auto& item = inv->GetItem(selectedIndex);
		auto availableActions = item.GetAvailableActions(player);

		for (size_t i = 0; i < availableActions.size(); ++i)
		{
			const auto& action = availableActions[i];

			sf::Text text;
			text.setFont(font);
			text.setCharacterSize(20);
			text.setFillColor(sf::Color::White);
			text.setString(action.name);
			text.setPosition(650.f, 150.f + i * 30.f); // offset
			actionTexts.push_back(text);

			actionTypes.push_back(action.type);   // запоминаем тип
		}

		if (!actionTexts.empty())
		{
			selectedActionIndex = 0;
			UpdateActionSelectorPosition();
		}
	}

	void InventoryScreen::UpdateSelectorPosition()
	{
		if (selectedIndex >= 0 && selectedIndex < static_cast<int>(itemTexts.size()))
		{
			sf::Vector2f pos = itemTexts[selectedIndex].getPosition();
			itemSelector.setPosition(pos.x - 10.f, pos.y - 5);
		}
	}

	void InventoryScreen::UpdateActionSelectorPosition()
	{
		if (selectedActionIndex < static_cast<int>(actionTexts.size()))
		{
			sf::Vector2f pos = actionTexts[selectedActionIndex].getPosition();
			actionSelector.setPosition(pos.x - 5.f, pos.y - 2);
		}
	}
}