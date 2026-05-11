#include "pch.h"
#include "GameWorld.h"
#include "InteractableComponent.h"
#include "UIManager.h"
#include "..//RogaliqueGame/InteractionMenu.h"

namespace XYZEngine
{
	GameWorld* GameWorld::Instance()
	{
		static GameWorld world;
		return &world;
	}

	void GameWorld::Update(float deltaTime)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Update(deltaTime);
		}
	}

	void GameWorld::FixedUpdate(float deltaTime)
	{
		fixedCounter += deltaTime;
		if (fixedCounter > PhysicsSystem::Instance()->GetFixedDeltaTime())
		{
			fixedCounter -= PhysicsSystem::Instance()->GetFixedDeltaTime();
			PhysicsSystem::Instance()->Update();
		}
	}

	void GameWorld::Render()
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->Render();
		}
	}

	void GameWorld::LateUpdate()
	{
		// Copy of marked to delete objects to avoid invalidation of iterators
		std::vector<GameObject*> toDestroy = markedToDestroyGameObjects;
		markedToDestroyGameObjects.clear();

		for (auto* obj : toDestroy)
		{
			// Check that object is still exist in world
			if (std::find_if(gameObjects.begin(), gameObjects.end(),
				[obj](const auto& up) { return up == obj; }) != gameObjects.end())
			{
				DestroyGameObjectImmediate(obj);
			}
		}
	}

	GameObject* GameWorld::CreateGameObject()
	{
		GameObject* newGameObject = new GameObject();
		gameObjects.push_back(newGameObject);
		return newGameObject;
	}

	GameObject* GameWorld::CreateGameObject(std::string name)
	{
		GameObject* newGameObject = new GameObject(name);
		gameObjects.push_back(newGameObject);
		return newGameObject;
		LOG_INFO("GameObject created : " + name);
	}

	void GameWorld::DestroyGameObject(GameObject* gameObject)
	{
		markedToDestroyGameObjects.push_back(gameObject);
	}

	void GameWorld::Clear()
	{
		for (int i = gameObjects.size() - 1; i >= 0; i--)
		{
			if (gameObjects[i] == nullptr)
			{
				continue;
			}

			if (gameObjects[i]->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				DestroyGameObjectImmediate(gameObjects[i]);
			}
		}

		fixedCounter = 0.f;
	}

	void GameWorld::ProcessInteract(GameObject* instigator)
	{
		if (!instigator) return;

		auto* playerTransform = instigator->GetComponent<TransformComponent>();
		if (!playerTransform) return;

		Vector2Df playerPos = playerTransform->GetWorldPosition();

		InteractableComponent* nearest = nullptr;
		GameObject* nearestObj = nullptr;
		float bestDist = 0.f;

		for (auto& go : gameObjects)
		{
			auto* interact = go->GetComponent<InteractableComponent>();
			if (!interact) continue;

			if (IsMarkedForDeletion(go))
				continue;

			auto* goTransform = go->GetComponent<TransformComponent>();
			if (!goTransform) continue;

			float dist = (goTransform->GetWorldPosition() - playerPos).GetLength();
			float radius = interact->GetInteractionRadius();

			if (dist <= radius)
			{
				if (!nearest || dist < bestDist)
				{
					nearest = interact;
					nearestObj = go;
					bestDist = dist;
				}
			}
		}

		if (nearest)
		{
			if (nearest->GetActions().size() == 1)
			{
			nearest->ExecuteAction(0, instigator);
			}
			else
			{
				// Show modal interaction menu
				UIManager::Instance()->PushScreen(std::make_shared<Ryzharto_RogaliqueGame::InteractionMenu>(nearestObj, instigator));
				LOG_INFO("GameWorld::ProcessInteract: InteractionMenu showed");
			}
		}
	}

	bool GameWorld::IsMarkedForDeletion(GameObject* obj) const
	{
		 return std::find(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(), obj) != markedToDestroyGameObjects.end();
	}

	void GameWorld::Print() const
	{
		for (auto& obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				obj->Print();
			}
		}
	}

	void GameWorld::DestroyGameObjectImmediate(GameObject* gameObject)
	{
		auto parent = gameObject->GetComponent<TransformComponent>()->GetParent();
		if (parent != nullptr)
		{
			parent->GetGameObject()->RemoveChild(gameObject);
		}

		for (auto transform : gameObject->GetComponentsInChildren<TransformComponent>())
		{
			GameObject* gameObjectToDelete = transform->GetGameObject();

			gameObjects.erase(std::remove_if(gameObjects.begin(), gameObjects.end(), [gameObjectToDelete](GameObject* obj) { return obj == gameObjectToDelete; }), gameObjects.end());
			markedToDestroyGameObjects.erase(std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(), [gameObjectToDelete](GameObject* obj) { return obj == gameObjectToDelete; }), markedToDestroyGameObjects.end());

			delete gameObjectToDelete;
		}
	}

}
