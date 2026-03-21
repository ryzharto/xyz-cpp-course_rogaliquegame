#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

namespace Ryzharto_ArcanoidGame
{
	class Block;

	class BlockFactory
	{
	protected:
		int createdBreakableBlocksCount = 0;

	public:
		virtual std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) = 0;
		virtual ~BlockFactory() = default;
		int GetCreatedBreakableBlocksCount();
		void ClearCounter();
	};

	class SimpleBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~SimpleBlockFactory() override = default;
	};

	class ThreeHitBlockFactory final : public BlockFactory
	{
	public:
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		  ~ThreeHitBlockFactory() override = default;
	};

	class UnbreakableBlockFactory final : public BlockFactory
	{
	public: 
		std::shared_ptr<Block> CreateBlock(const sf::Vector2f& position) override;
		~UnbreakableBlockFactory() override = default;
	};
}