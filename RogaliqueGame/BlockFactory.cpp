#include "BlockFactory.h"
#include "Block.h"

namespace Ryzharto_ArcanoidGame
{
	int BlockFactory::GetCreatedBreakableBlocksCount()
	{
		return createdBreakableBlocksCount;
	}

	void BlockFactory::ClearCounter()
	{
		createdBreakableBlocksCount = 0;
	}

	std::shared_ptr<Block> SimpleBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreakableBlocksCount;
		return std::make_shared<SmoothDestroyableBlock>(position);
	}

	std::shared_ptr<Block> UnbreakableBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		return std::make_shared<UnbreakableBlock>(position);
	}

	std::shared_ptr<Block> ThreeHitBlockFactory::CreateBlock(const sf::Vector2f& position)
	{
		++createdBreakableBlocksCount;
		return std::make_shared<ThreeHitBlock>(position);
	}
}