#include "LevelManager.h"
#include "Game.h"
#include "GameWorld.h"
#include "InventoryComponent.h"
#include "WeaponComponent.h"
#include "StatsComponent.h"
#include "Item.h"
#include "PrefabCatalog.h"
#include "UIManager.h"
#include "LevelTransitionScreen.h"
#include "Logger.h"

namespace Ryzharto_RogaliqueGame
{
    LevelManager& LevelManager::Instance()
    {
        static LevelManager instance;
        return instance;
    }

    void LevelManager::RegisterLevel(const std::string& name, const std::string& description, LevelFactory factory)
    {
        levels.push_back({ name, description, factory });
        XYZEngine::LOG_INFO("Level registered: " + name);
    }

    void LevelManager::LoadLevel(const std::string& name)
    {
        // Ищем уровень по имени
        auto it = std::find_if(levels.begin(), levels.end(),
            [&name](const LevelInfo& info) { return info.name == name; });
        if (it == levels.end())
        {
            XYZEngine::LOG_ERROR("Level not found: " + name);
            return;
        }

        currentIndex = std::distance(levels.begin(), it);
        // Очищаем мир и UI
        XYZEngine::GameWorld::Instance()->Clear();
        XYZEngine::UIManager::Instance()->ClearAllScreens();

        // Показываем экран перехода
        auto screen = std::make_shared<LevelTransitionScreen>(it->name, it->description);
        XYZEngine::UIManager::Instance()->PushScreen(screen);

        // Вызываем фабрику, которая создаст уровень и игрока
        it->factory(&Game::Instance());

        Game::Instance().OnLevelLoaded();
    }

    void LevelManager::LoadNextLevel()
    {
        if (levels.empty()) return;

        // Сохраняем состояние текущего игрока
        auto* player = Game::Instance().GetPlayer();
        if (player)
            SavePlayerState(player);

        int nextIndex = (currentIndex + 1) % levels.size(); // зациклим для демо
        currentIndex = nextIndex;
        const auto& info = levels[nextIndex];

        // Очищаем мир и UI
        XYZEngine::GameWorld::Instance()->Clear();
        XYZEngine::UIManager::Instance()->ClearAllScreens();

        // Показываем экран перехода
        auto screen = std::make_shared<LevelTransitionScreen>(info.name, info.description);
        XYZEngine::UIManager::Instance()->PushScreen(screen);

        // Создаём новый уровень
        info.factory(&Game::Instance());

        // Восстанавливаем состояние игрока на новом уровне
        auto* newPlayer = Game::Instance().GetPlayer();
        if (newPlayer)
            RestorePlayerState(newPlayer);

        // Add HUD
        Game::Instance().OnLevelLoaded();
    }

    void LevelManager::SavePlayerState(XYZEngine::GameObject* player)
    {
        if (!player) return;

        // Статы
        auto* stats = player->GetComponent<XYZEngine::StatsComponent>();
        if (stats)
        {
            playerState.health = stats->GetCurrentHealth();
            playerState.armour = stats->GetCurrentArmour();
            playerState.stamina = stats->GetCurrentStamina();
        }

        // Инвентарь
        auto* inventory = player->GetComponent<XYZEngine::InventoryComponent>();
        playerState.inventoryItems.clear();
        if (inventory)
        {
            for (size_t i = 0; i < inventory->GetItemCount(); ++i)
            {
                const auto& item = inventory->GetItem(i);
                ItemSaveData data;
                data.prefabKey = item.GetPrefabKey();
                data.dynamicData = item.dynamicData;
                playerState.inventoryItems.push_back(data);
            }
        }

        // Оружие
        auto* weapon = player->GetComponent<XYZEngine::WeaponComponent>();
        playerState.weapons.clear();
        if (weapon)
        {
            int currentIdx = weapon->GetCurrentWeaponIndex();
            for (int i = 0; i < weapon->GetWeaponCount(); ++i)
            {
                
            }
            // Временно сохраним только текущее оружие
            playerState.currentWeaponIndex = currentIdx;
            playerState.weapons.push_back(weapon->GetCurrentWeaponInfo());
        }
    }

    void LevelManager::RestorePlayerState(XYZEngine::GameObject* player)
    {
        if (!player) return;

        // Статы
        auto* stats = player->GetComponent<XYZEngine::StatsComponent>();
        if (stats)
        {
            stats->SetHealth(playerState.health);
            stats->SetArmour(playerState.armour);
            stats->SetStamina(playerState.stamina);
        }

        // Инвентарь
        auto* inventory = player->GetComponent<XYZEngine::InventoryComponent>();
        if (inventory)
        {
            // Очищаем инвентарь (на старте он пуст, но на всякий случай)
            while (inventory->GetItemCount() > 0)
                inventory->RemoveItem(0);

            for (auto& data : playerState.inventoryItems)
            {
                const Prefab* prefab = PrefabCatalog::Instance().GetPrefab(data.prefabKey);
                if (prefab)
                {
                    Item item = Item::CreateFromPrototype(*prefab);
                    item.dynamicData = data.dynamicData;
                    inventory->AddItem(item);
                }
            }
        }

        // Оружие
        auto* weapon = player->GetComponent<XYZEngine::WeaponComponent>();
        if (weapon)
        {
            // Очищаем арсенал
            while (weapon->GetWeaponCount() > 0)
                weapon->RemoveWeapon(weapon->GetCurrentWeaponInfo().name); // неэффективно, но для демо

            for (auto& info : playerState.weapons)
            {
                weapon->AddWeapon(info);
            }
            weapon->SetCurrentWeaponIndex(playerState.currentWeaponIndex);
        }
    }
}