#pragma once
#include "Component.h"
#include "..//RogaliqueGame/Item.h"
#include <vector>

namespace XYZEngine
{
	class InventoryComponent : public Component
	{
	public:
		InventoryComponent(GameObject* gameObject);
		void Update(float deltaTime) override {}
		void Render() override {}

		void AddItem(const Ryzharto_RogaliqueGame::Item& item);
		void RemoveItem(size_t index);
		size_t GetItemCount() const { return items.size(); }
		const Ryzharto_RogaliqueGame::Item& GetItem(size_t index) const { return items.at(index); }
		bool UseItem(size_t itemIndex, Ryzharto_RogaliqueGame::ItemActionType actionType, GameObject* owner); // for UseItem with one index of actions call UseItem(itemIndex, 0, owner)

	private:
		std::vector<Ryzharto_RogaliqueGame::Item> items;
	};
}

