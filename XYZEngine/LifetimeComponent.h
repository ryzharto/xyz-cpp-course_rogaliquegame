#pragma once
#include "GameObject.h"

namespace XYZEngine
{
	class LifetimeComponent : public Component
	{
	public:
		LifetimeComponent(GameObject* gameObject);
		void Update(float deltaTime) override;
		void Render() override {}
		void SetLifetime(float lifetime) { remainingTime = lifetime;  }

	private:
		float remainingTime = 0.f;
	};
}


