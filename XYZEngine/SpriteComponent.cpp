#include "pch.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"

namespace XYZEngine
{
	SpriteComponent::SpriteComponent(GameObject* gameObject) : Component(gameObject)
	{
		sprite = std::make_unique<sf::Sprite>();
		scale = { 1, -1 };
		sprite->setScale({ 1,-1 });
		transform = gameObject->GetComponent<TransformComponent>();
	}

	SpriteComponent::~SpriteComponent()
	{

	}

	void SpriteComponent::Update(float deltaTime)
	{

	}

	void SpriteComponent::Render()
	{
		if (sprite != nullptr)
		{
			sprite->setPosition(Convert<sf::Vector2f, Vector2Df>(transform->GetWorldPosition()));
			sprite->setRotation(transform->GetWorldRotation());

			auto transformScale = Convert<sf::Vector2f, Vector2Df>(transform->GetWorldScale());
			sprite->setScale({ scale.x * transformScale.x, scale.y * transformScale.y });
			RenderSystem::Instance()->Render(*sprite);
		}
	}

	const sf::Sprite* SpriteComponent::GetSprite() const
	{
		return sprite.get();
	}

	void SpriteComponent::SetTexture(const sf::Texture& newTexture)
	{
		sprite->setTexture(newTexture);
		auto textureSize = sprite->getTexture()->getSize();
		sprite->setOrigin({ 0.5f * textureSize.x, 0.5f * textureSize.y });
	}

	void SpriteComponent::SetPixelSize(int newWidth, int newHeight)
	{
		auto originalSize = sprite->getTexture()->getSize();
		scale = { (float)newWidth / (float)originalSize.x, -(float)newHeight / (float)originalSize.y };
	}

	void SpriteComponent::FlipX(bool flip)
	{
		if (flip != isFlipX)
		{
			scale = { -scale.x, scale.y };
			isFlipX = flip;
		}
	}

	void SpriteComponent::FlipY(bool flip)
	{
		if (flip != isFlipY)
		{
			scale = { scale.x, -scale.y };
			isFlipY = flip;
		}
	}
}