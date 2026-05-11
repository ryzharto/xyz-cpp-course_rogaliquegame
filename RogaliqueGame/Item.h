#pragma once
#include "Prefab.h"
#include <string>
#include <vector>
#include <functional>

namespace Ryzharto_RogaliqueGame
{
	struct Prefab; // forward-декларация

	struct ItemAction
	{
		std::string name; // "Use", "Equip", "Drop", "Discard" etc...
		std::function<void(XYZEngine::GameObject* owner)> execute;
	};

	struct Item
	{
		Item() = default;

		std::string name;
		std::string description;
		std::string prefabKey;           // prefab key used for drop action
		std::string iconTextureKey;      // texture key for inventory UI
		std::vector<ItemAction> actions; // list of available actions with item

		//std::function<void(XYZEngine::GameObject* owner)> onUse;
				
		Item(const std::string& name, const std::string& desc, const std::vector<ItemAction>& acts) : name(name), description(desc), actions(acts) {}
		static Item CreateFromPrefab(const Prefab& prefab);
	};
}