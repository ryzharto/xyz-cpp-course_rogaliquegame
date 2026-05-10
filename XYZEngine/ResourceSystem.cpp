#include "pch.h"
#include "ResourceSystem.h"
#include "Logger.h"
#include <cassert>

namespace XYZEngine
{
	ResourceSystem* ResourceSystem::Instance()
	{
		static ResourceSystem resourceSystem;
		return &resourceSystem;
	}

	// Textures
	void ResourceSystem::LoadTexture(const std::string& name, std::string sourcePath, bool isSmooth)
	{
		if (textures.find(name) != textures.end())
		{
			return;
		}

		auto newTexture = std::make_unique<sf::Texture>();
		if (!newTexture->loadFromFile(sourcePath))
		{
			LOG_ERROR("Failed to load texture '" + name + "' from '" + sourcePath + "'");
			throw std::runtime_error("Texture loading failed" + name);
		}

		newTexture->setSmooth(isSmooth);
		textures.emplace(name, std::move(newTexture));
		LOG_INFO("Texture loaded: " + name + " (" + sourcePath + ")");
	}

	const sf::Texture* ResourceSystem::GetTextureShared(const std::string& name) const
	{
		auto it = textures.find(name);
		if (it == textures.end())
		{
			LOG_WARN("ResourceSystem::GetTextureShader: Resource '" + name + "' not found in cache");
			assert(false);
			return nullptr;
		}

		return it->second.get();
	}

	sf::Texture* ResourceSystem::GetTextureCopy(const std::string& name) const
	{
		auto it = textures.find(name);
		if (it == textures.end())
		{
			LOG_WARN("ResourceSystem::GetTextureCopy: Resource '" + name + "' not found in cache");
			assert(false);
			return nullptr;
		}

		return new sf::Texture(*it->second);		
	}

	void ResourceSystem::DeleteSharedTexture(const std::string& name)
	{
		textures.erase(name);
		LOG_INFO("ResourceSystem::DeleteSharedTexture: Texture deleted: " + name);
	}

	// Texture maps
	void ResourceSystem::LoadTextureMap(const std::string& name, std::string sourcePath, sf::Vector2u elementPixelSize, int totalElements, bool isSmooth)
	{
		if (textureMaps.find(name) != textureMaps.end())
		{
			return;
		}

		sf::Texture textureMap;
		if (textureMap.loadFromFile(sourcePath))
		{
			auto textureMapElements = new std::vector<sf::Texture*>();

			auto textureSize = textureMap.getSize();
			int loadedElements = 0;

			for (unsigned int y = 0; y <= textureSize.y - elementPixelSize.y; y += elementPixelSize.y)
			{
				if (loadedElements == totalElements)
				{
					break;
				}

				for (unsigned int x = 0; x <= textureSize.x - elementPixelSize.x; x += elementPixelSize.x)
				{
					if (loadedElements == totalElements)
					{
						break;
					}

					sf::Texture* newTextureMapElement = new sf::Texture();
					if (newTextureMapElement->loadFromFile(sourcePath, sf::IntRect(x, y, elementPixelSize.x, elementPixelSize.y)))
					{
						newTextureMapElement->setSmooth(isSmooth);
						textureMapElements->push_back(newTextureMapElement);
					}
					loadedElements++;
				}
			}
			textureMaps.emplace(name, *textureMapElements);
			LOG_INFO("ResourceSystem::LoadTextureMap: Texture map loaded: " + name + " (" + sourcePath + ")");
		}
		else
		{
			LOG_ERROR("ResourceSystem::LoadTextureMap: Failed to load texture map '" + name + "' from '" + sourcePath + "'");
			assert(false);
			throw std::runtime_error("Texture map loading failed");
		}
	}

	const sf::Texture* ResourceSystem::GetTextureMapElementShared(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		if (textureMap == textureMaps.end())
		{
			LOG_WARN("ResourceSystem::GetTextureMapElementShared: Texture map '" + name + "' not found in cache");
			assert(false);
			return nullptr;
		}

		auto textures = textureMap->second;
		if (elementIndex < 0 || elementIndex >= static_cast<int>(textures.size()))
		{
			LOG_WARN("ResourceSystem::GetTextureMapElementShared: Texture map element index '" + std::to_string(elementIndex) + "' is out of range [0, " + std::to_string(textures.size() - 1) + "] for map '" + name + "'");
			assert(false);
			return nullptr;
		}

		return textures[elementIndex];
	}

	sf::Texture* ResourceSystem::GetTextureMapElementCopy(const std::string& name, int elementIndex) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return new sf::Texture(*textures[elementIndex]);
	}

	int ResourceSystem::GetTextureMapElementsCount(const std::string& name) const
	{
		auto textureMap = textureMaps.find(name);
		auto textures = textureMap->second;
		return textures.size();
	}

	void ResourceSystem::DeleteSharedTextureMap(const std::string& name)
	{
		auto textureMap = textureMaps.find(name);
		auto deletingTextures = textureMap->second;

		for (int i = 0; i < deletingTextures.size(); i++)
		{
			delete deletingTextures[i];
		}

		textureMaps.erase(textureMap);
	}

	// Sounds
	void ResourceSystem::LoadSound(const std::string& name, std::string sourcePath)
	{
		if (sounds.find(name) != sounds.end())
			return;

		auto newSound = std::make_unique<sf::SoundBuffer>();
		if (!newSound->loadFromFile(sourcePath))
		{
			LOG_ERROR("ResourceSystem::LoadSound: Failed to load sound '" + name + "' from '" + sourcePath + "'");
			assert(false);
			throw std::runtime_error("Sound loading failed");
		}

		sounds.emplace(name, std::move(newSound));
		LOG_INFO("Sound loaded: " + name + " (" + sourcePath + ")");
	}

	const sf::SoundBuffer* ResourceSystem::GetSound(const std::string& name) const
	{
		auto it = sounds.find(name);
		if (it == sounds.end())
		{
			LOG_WARN("ResourceSystem::GetSound: Resource '" + name + "' not found in cache");
			assert(false);
			return nullptr;
		}

		return it->second.get();
	}

	void ResourceSystem::DeleteSound(const std::string& name)
	{
		sounds.erase(name);
		LOG_INFO("ResourceSystem::DeleteSound: Sound deleted: " + name);
	}

	void ResourceSystem::Clear()
	{
		DeleteAllTextures();
		DeleteAllTextureMaps();
		DeleteAllSounds();
		LOG_INFO("ResourceSystem cleared");
	}

	void ResourceSystem::DeleteAllTextures()
	{
		textures.clear();
	}

	void ResourceSystem::DeleteAllTextureMaps()
	{
		std::vector<std::string> keysToDelete;

		for (const auto& textureMapPair : textureMaps)
		{
			keysToDelete.push_back(textureMapPair.first);
		}

		for (const auto& key : keysToDelete)
		{
			DeleteSharedTextureMap(key);
		}
	}

	void ResourceSystem::DeleteAllSounds()
	{
		sounds.clear();
	}
}