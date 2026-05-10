#pragma once
#include <string>
#include <functional>

namespace Ryzharto_RogaliqueGame
{
	struct ItemAction
	{
		std::string name; // "Use", "Equip", "Drop" etc...
		std::function<void(XYZEngine::GameObject* owner)> execute;
	};

	struct Item
	{
		Item() = default;

		std::string name;
		std::string description;
		std::vector<ItemAction> actions; // list of available actions with item

		//std::function<void(XYZEngine::GameObject* owner)> onUse;
				
		Item(const std::string& name, const std::string& desc, const std::vector<ItemAction>& acts) : name(name), description(desc), actions(acts) {}
	};
}