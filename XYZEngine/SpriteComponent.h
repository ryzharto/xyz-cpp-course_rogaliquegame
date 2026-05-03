#pragma once
#include "TransformComponent.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace XYZEngine
{
	class SpriteComponent : public Component
	{
	public:
		SpriteComponent(GameObject* gameObject);
		~SpriteComponent();

		void Update(float deltaTime) override;
		void Render() override;

		const sf::Sprite* GetSprite() const;
		void SetTexture(const sf::Texture& newTexture);
		void SetPixelSize(int newWidth, int newHeight);

		void FlipX(bool flip);
		void FlipY(bool flip);

	private:
		Vector2Df scale;
		std::unique_ptr<sf::Sprite> sprite;
		TransformComponent* transform;

		bool isFlipX = false;
		bool isFlipY = false;
	};

}

