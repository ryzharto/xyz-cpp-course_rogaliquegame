#include "LevelLoader.h"
#include "GameSettings.h"
#include <fstream>
#include <assert.h>
#include <filesystem>

namespace Ryzharto_RogaliqueGame
{
	Level& LevelLoader::GetLevel(int i)
	{
		return levels.at(i);
	}

	void LevelLoader::LoadLevelsFromFile()
	{
		std::string filepath = SETTINGS.LEVELS_CONFIG_PATH;
		std::string line;
		std::ifstream file(filepath);
		int y = 0;

		while (getline(file, line))
		{
			if (line.rfind("level ", 0) == 0)
			{
				auto level = std::stoi(line.substr(6, line.size() - 6));
				levels.emplace_back(Level());
				y = 0;
			}
			else
			{
				int x = 0;
				for (char c : line)
				{
					if (c != ' ')
					{
						
					}
					++x;
				}
			}
			++y;
		}
		file.close();
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}
}
