#include "HUD.h"
#include "GameObject.h"
#include "StatsComponent.h"
#include "WeaponComponent.h"
#include "ResourceSystem.h"
#include "RenderSystem.h"
#include "GameSettings.h"
#include <sstream>

namespace Ryzharto_RogaliqueGame
{
	HUD::HUD(XYZEngine::GameObject* player) : player(player)
	{
		SetModal(false); // HUD does not blocking input
	}

	void HUD::Init()
	{
		// Font
		if (!font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"))
		{
			XYZEngine::LOG_ERROR("Failed to load font for HUD");
			throw std::runtime_error("Font loading failed");
			return;
		}

		// WeaponIcon
		if (weaponIconTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "weapon_ppk-20.png"))
		{
			weaponIcon.setTexture(weaponIconTexture);
			sf::Vector2u texSize = weaponIconTexture.getSize();
			weaponIcon.setScale(iconSize.x / texSize.x, iconSize.y / texSize.y);
			weaponIcon.setPosition(1280 - iconSize.x - margin, 720 - iconSize.y - margin * 3);
		}
		else
			XYZEngine::LOG_WARN("Weapon icon texture not found, icon will be hidden");

		// Texts
		auto createText = [&](sf::Text& text, unsigned size, sf::Color color, float posX, float posY)
			{
				text.setFont(font);
				text.setCharacterSize(size);
				text.setFillColor(color);
				text.setPosition(posX, posY);
			};

		createText(armourText, 18, sf::Color(128,128,128), 60, 12);
		createText(healthText, 18, sf::Color::Green, 60, 52);
		createText(staminaText, 18, sf::Color::Yellow, 60, 92);
		createText(ammoText, 30, sf::Color::White, weaponIcon.getPosition().x, weaponIcon.getPosition().y + iconSize.y + margin);

		// Armour bar background
		armourBarBg.setSize(barSize);
		armourBarBg.setFillColor(sf::Color(30, 30, 30));
		armourBarBg.setPosition(60, 32);

		// Armour bar fill
		armourBarFill.setSize(barSize);
		armourBarFill.setFillColor(sf::Color(128, 128, 128));
		armourBarFill.setPosition(60, 32);

		// Health bar background
		healthBarBg.setSize(barSize);
		healthBarBg.setFillColor(sf::Color(30, 30, 30));
		healthBarBg.setPosition(60, 72);

		// Health bar fill
		healthBarFill.setSize(barSize);
		healthBarFill.setFillColor(sf::Color::Green);
		healthBarFill.setPosition(60, 72);

		// Stamina bar background
		staminaBarBg.setSize(barSize);
		staminaBarBg.setFillColor(sf::Color(30, 30, 30));
		staminaBarBg.setPosition(60, 112);

		// Stamina bar fill
		staminaBarFill.setSize(barSize);
		staminaBarFill.setFillColor(sf::Color::Yellow);
		staminaBarFill.setPosition(60, 112);
	}

	void HUD::Update(float deltaTime)
	{
		if (!player) return;

		auto stats = player->GetComponent<XYZEngine::StatsComponent>();
		auto weapon = player->GetComponent<XYZEngine::WeaponComponent>();

		if (stats)
		{
			float armor = stats->GetCurrentArmour();
			float maxArmour = stats->GetMaxArmour();
			float hp = stats->GetCurrentHealth();
			float maxHP = stats->GetMaxHealth();
			float sp = stats->GetCurrentStamina();
			float maxSP = stats->GetMaxStamina();

			armourText.setString("ARM " + std::to_string((int)armor) + "/" + std::to_string((int)maxArmour));
			healthText.setString("HP " + std::to_string((int)hp) + "/" + std::to_string((int)maxHP));
			staminaText.setString("SP " + std::to_string((int)sp) + "/" + std::to_string((int)maxSP));

			float armourRatio = (maxArmour > 0.f) ? (armor / maxArmour) : 0.f;
			armourBarFill.setSize({ barSize.x * armourRatio, barSize.y });

			float hpRatio = (maxHP > 0.f) ? (hp / maxHP) : 0.f;
			healthBarFill.setSize({ barSize.x * hpRatio, barSize.y });

			float spRatio = (maxSP > 0.f) ? (sp / maxSP) : 0.f;
			staminaBarFill.setSize({ barSize.x * spRatio, barSize.y });
		}

		if (weapon)
		{
			std::stringstream ss;
			if (weapon->IsReloading())
			{
				int progress = (int)(weapon->GetReloadProgress() * 100.f);
				ss << "Reloading..."<< progress << "%";
			}
			else
			{
				ss << weapon->GetCurrentAmmo() << "/" << weapon->GetMaxAmmo();
			}
			ammoText.setString(ss.str());
			float offset = ammoText.getLocalBounds().width;
			ammoText.setPosition(weaponIcon.getPosition().x + iconSize.x - offset, weaponIcon.getPosition().y + iconSize.y + margin);
		}

	}

	void HUD::Draw(sf::RenderWindow& window)
	{
		window.draw(armourBarBg);
		window.draw(armourBarFill);
		window.draw(healthBarBg);
		window.draw(healthBarFill);
		window.draw(staminaBarBg);
		window.draw(staminaBarFill);
		window.draw(armourText);
		window.draw(healthText);
		window.draw(staminaText);
		window.draw(ammoText);

		// Weapon Icon
		if (weaponIcon.getTexture() != nullptr)
			window.draw(weaponIcon);
	}

}