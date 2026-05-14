#pragma once
#include <string>
#include <vector>
#include <functional>

namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
	// Item actions
	enum class ItemActionType
	{
		None = 0,
		Use,
		Equip,
		Unequip,
		Drop,
		Destroy,
		Combine,
		Examine
	};

	// Item categories
	enum class ItemCategory
	{
		None = 0,
		Weapon,
		Armor,
		Consubable,
		KeyItem,
		Quest,
		Misc
	};

	struct ItemDynamicData
	{
		int currentAmmo = -1; // -1 means that "not applied"
		// In future: durability, charges, ect
	};

	struct ItemAction
	{
		ItemActionType type = ItemActionType::None;
		std::string name; // "Use", "Equip", "Drop", "Discard" etc...
		std::function<void(XYZEngine::GameObject* owner, struct Item* item)> execute;
		bool keepItem = false; //if true keep item in inventory after use 
	};
}