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
		LOG_INFO("InventoryComponent::AddItem: Item added: " + item.GetName());
	}

	void InventoryComponent::RemoveItem(size_t index)
	{
		if (index < items.size())
		{
			LOG_INFO("Item removed: " + items[index].GetName());
			items.erase(items.begin() + index);
		}
	}

	bool InventoryComponent::UseItem(size_t itemIndex, Ryzharto_RogaliqueGame::ItemActionType actionType, GameObject* owner)
	{
		if (itemIndex >= items.size()) return false;

		const auto& item = items[itemIndex];
		auto available = item.GetAvailableActions(owner);

		// »щем действие с нужным типом
		for (auto& action : available)
		{
			if (action.type == actionType)
			{
				if (action.execute != nullptr)
				{
					LOG_INFO("Executing action: " + action.name);
					action.execute(owner, &items[itemIndex]);
					if (!action.keepItem)
						RemoveItem(itemIndex);
					return true;
				}
			}
		}
		return false;
	}

}