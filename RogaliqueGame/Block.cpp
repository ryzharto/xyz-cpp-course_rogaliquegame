#include "Block.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>

namespace Ryzharto_ArcanoidGame
{
	Block::Block(const sf::Vector2f position) : GameObject(SETTINGS.RESOURCES_PATH + "block.png", position, SETTINGS.BLOCK_WIDTH, SETTINGS.BLOCK_HEIGHT)
	{
		sf::Color color;
		color.r = rand() % 255;
		color.g = rand() % 255;
		color.b = rand() % 255;
		sprite.setColor(color);
	}

	Block::~Block()
	{

	}

	void Block::Update(float timeDelta)
	{

	}

	bool Block::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);

		sf::FloatRect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;
		Emit();
	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	/*
	// Smooth Destroyable Block
	*/
	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position) : Block(position)
	{

	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::FloatRect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(SETTINGS.BREAK_DELAY);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
		Emit();
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		color = sprite.getColor();
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}

	/*
	// Unbreakable Block
	*/
	UnbreakableBlock::UnbreakableBlock(const sf::Vector2f& position) : Block(position)
	{
		sf::Color color;
		color.r = 105;
		color.g = 105;
		color.b = 105;
		sprite.setColor(color);
	}

	void UnbreakableBlock::OnHit()
	{
		//--hit_count ;
	}

	/*
	// ThreeHit Block
	*/
	ThreeHitBlock::ThreeHitBlock(const sf::Vector2f& position) : SmoothDestroyableBlock(position)
	{
		assert(oneHitTexture.loadFromFile(SETTINGS.RESOURCES_PATH + "block_oneHit.png"));
		assert(twoHitTexture.loadFromFile(SETTINGS.RESOURCES_PATH + "block_twoHit.png"));

		hitCount = 3;
		sprite.setColor(sf::Color::Magenta);
	}

	void ThreeHitBlock::OnHit()
	{
		--hitCount;
		StageChange();

		if (hitCount == 0)
		{
			hitCount = 1;
			StartTimer(SETTINGS.BREAK_DELAY);
		}
	}

	void ThreeHitBlock::StageChange()
	{
		if (hitCount == 2)
			color = sprite.getColor();
			sprite.setTexture(oneHitTexture);
			sprite.setColor(color);

		if (hitCount < 2)
		{
			color = sprite.getColor();
			sprite.setTexture(twoHitTexture);
			sprite.setColor(color);
			//sprite.setTexture(twoHitTexture);
			//sprite.setColor(sf::Color::Green);
			//color = sf::Color::Green;
		}
	}

	/*
	// Glass Block
	*/
	GlassBlock::GlassBlock(const sf::Vector2f& position) : Block(position)
	{
		hitCount = 1;
		sf::Color color;
		color.r = rand() % 255;
		color.g = rand() % 255;
		color.b = rand() % 255;
		color.a = 100;
		sprite.setColor(color);
	}
}