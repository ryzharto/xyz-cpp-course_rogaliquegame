#pragma once
#include "Prefab.h"
#include "ItemData.h"
#include <optional>

namespace XYZEngine { class GameObject; }

namespace Ryzharto_RogaliqueGame
{
	struct Item
	{
		const Prefab* prototype = nullptr;
		ItemDynamicData dynamicData;

		const std::string& GetName() const { return prototype->name; }
		const std::string& GetPrefabKey() const { return prototype->key; }
		const std::string& GetIconTextureKey() const { return prototype->textureKey; }
		ItemCategory GetCategory() const { return prototype->category; }
		const std::optional<XYZEngine::WeaponInfo>& GetWeaponData() const { return prototype->weaponData; }

		std::vector<ItemAction> GetAvailableActions(XYZEngine::GameObject* owner) const; // Returns actions available it current moment (takes in count equipment and etc.)
		static Item CreateFromPrototype(const Prefab& prefab);

		//Item() = default;

		//std::string name;
		//std::string description;
		//std::string prefabKey; // prefab key used for drop action
		//std::string iconTextureKey; // texture key for inventory UI
		//std::string weaponName; // for weapons - must be unique
		//ItemCategory category = ItemCategory::None; // item category
		//std::vector<ItemAction> actions; // list of available actions with item (unsorted)
		//std::optional<XYZEngine::WeaponInfo> weaponData;
		//ItemDynamicData dynamicData;

		//std::function<void(XYZEngine::GameObject* owner)> onUse;
		
		//Item(const std::string& name, const std::string& desc, const std::vector<ItemAction>& acts) : name(name), description(desc), actions(acts) {}
		
	};
}