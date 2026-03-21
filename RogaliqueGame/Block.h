#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "GameObject.h"
#include "ICollidable.h"
#include "IDelayedAction.h"
#include "IObserver.h"

namespace Ryzharto_ArcanoidGame
{
	// Player data
	class Block : public GameObject, public ICollidable, public IObservable
	{
	protected:
		void OnHit();
		int hitCount = 1;
	public:
		Block(const sf::Vector2f position);
		virtual ~Block();
		void Update(float timeDelta) override;

		bool GetCollision(std::shared_ptr<ICollidable> collidable) const override;
		bool IsBroken();

		//const sf::Vector2f position;
		//const sf::Color& color = sf::Color::Magenta;		
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;
	public:
		SmoothDestroyableBlock(const sf::Vector2f& position);
		~SmoothDestroyableBlock() = default;
		void Update(float timeDelta) override;

		bool GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
	};

	class UnbreakableBlock : public Block
	{
	public:
		UnbreakableBlock(const sf::Vector2f& position);
		void OnHit() override;
		void Update(float)
		{
			int i = 0;
			++i;
		};
	};

	class ThreeHitBlock : public SmoothDestroyableBlock
	{
	public:
		ThreeHitBlock(const sf::Vector2f& position);

	private:
		void OnHit() override;
		void StageChange();

		sf::Texture oneHitTexture;
		sf::Texture twoHitTexture;
	};

	class GlassBlock : public Block
	{
	public:
		GlassBlock(const sf::Vector2f& position);

	};
}
