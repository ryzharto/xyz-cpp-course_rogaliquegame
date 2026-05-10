#include "pch.h"
#include "InventoryComponent.h"

namespace XYZEngine
{
	InventoryComponent::InventoryComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	void InventoryComponent::AddItem(const Ryzharto_RogaliqueGame::Item& item)
	{
		items.push_back(item);
		LOG_INFO("InventoryComponent::AddItem: Item added: " + item.name);
	}

	void InventoryComponent::RemoveItem(size_t index)
	{
		if (index < items.size())
		{
			LOG_INFO("Item removed: " + items[index].name);
			items.erase(items.begin() + index);
		}
	}

	bool InventoryComponent::UseItem(size_t itemIndex, size_t actionIndex, GameObject* owner)
	{
		if (itemIndex >= items.size()) return false;

		const auto& actions = items[itemIndex].actions;
		if (actionIndex >= actions.size()) return false;

		auto& action = actions[actionIndex];
		if (action.execute)
		{
			action.execute(owner);
			RemoveItem(itemIndex); // destroy object after using
			return true;
		}
		return false;
	}

}