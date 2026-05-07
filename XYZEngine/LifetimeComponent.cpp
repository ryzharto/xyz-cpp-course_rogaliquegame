#include "pch.h"
#include "LifetimeComponent.h"
#include "GameWorld.h"

namespace XYZEngine
{
	LifetimeComponent::LifetimeComponent(GameObject* gameObject) : Component(gameObject)
	{ }

	void LifetimeComponent::Update(float deltaTime)
	{
		remainingTime -= deltaTime;

		if (remainingTime <= 0.f)
		{
			GameWorld::Instance()->DestroyGameObject(gameObject);
			LOG_INFO("GameObject " + gameObject->GetName() + " deleted");
		}
	}
}