#pragma once
#include <vector>
#include <string>
#include <memory>
#include <map>

namespace Ryzharto_RogaliqueGame
{
	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreakable
	};

	struct Level
	{
		
	};

	class LevelLoader final
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();
	
	private:
		void LoadLevelsFromFile();

		std::vector<Level> levels;
	};
}
