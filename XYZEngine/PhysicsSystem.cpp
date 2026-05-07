#include "pch.h"
#include "PhysicsSystem.h"

namespace XYZEngine
{
	PhysicsSystem* PhysicsSystem::Instance()
	{
		static PhysicsSystem physicsSystem;
		return &physicsSystem;
	}

	float PhysicsSystem::GetFixedDeltaTime() const
	{
		return fixedDeltaTime;
	}

    /*void PhysicsSystem::Update()
    {
        // -----------------------------------------------------------------
        // 1. §³§Ò§à§â §Ó§ã§Ö§ç §á§Ñ§â §Ü§à§Ý§Ý§Ú§Ù§Ú§Û (§à§Ò§ß§Ñ§â§å§Ø§Ö§ß§Ú§Ö)
        // -----------------------------------------------------------------
        struct CollisionPair
        {
            ColliderComponent* first;
            ColliderComponent* second;
            sf::FloatRect intersection;
            bool isTrigger = false;   // true, §Ö§ã§Ý§Ú §à§Õ§Ú§ß §Ú§Ù §å§é§Ñ§ã§ä§ß§Ú§Ü§à§Ó ¨C §ä§â§Ú§Ô§Ô§Ö§â
        };
        std::vector<CollisionPair> pairs;

        for (size_t i = 0; i < colliders.size(); ++i)
        {
            ColliderComponent* colA = colliders[i];
            if (!colA) continue;

            GameObject* objA = colA->GetGameObject();
            RigidbodyComponent* bodyA = objA ? objA->GetComponent<RigidbodyComponent>() : nullptr;
            bool kinematicA = bodyA && bodyA->GetKinematic();
            bool staticA = colA->IsStatic();

            for (size_t j = i + 1; j < colliders.size(); ++j)
            {
                ColliderComponent* colB = colliders[j];
                if (!colB) continue;

                bool staticB = colB->IsStatic();

                // §±§Ñ§â§Ñ §ã§ä§Ñ§ä§Ú§Ü§Ñ-§ã§ä§Ñ§ä§Ú§Ü§Ñ §Ú§Ô§ß§à§â§Ú§â§å§Ö§ä§ã§ñ
                if (staticA && staticB)
                    continue;

                sf::FloatRect intersection;
                if (!colA->bounds.intersects(colB->bounds, intersection))
                    continue;

                bool triggerPair = (colA->isTrigger || colB->isTrigger);
                pairs.push_back({ colA, colB, intersection, triggerPair });
            }
        }

        // -----------------------------------------------------------------
        // 2. §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §ä§â§Ú§Ô§Ô§Ö§â§à§Ó (§ä§à§Ý§î§Ü§à §ã§à§Ò§í§ä§Ú§Û§ß§Ñ§ñ §é§Ñ§ã§ä§î)
        // -----------------------------------------------------------------
        for (auto& pair : pairs)
        {
            if (!pair.isTrigger) continue;
            // §´§â§Ú§Ô§Ô§Ö§â §ã§â§Ñ§Ò§Ñ§ä§í§Ó§Ñ§Ö§ä §ä§à§Ý§î§Ü§à §Ö§ã§Ý§Ú §à§Õ§Ú§ß §ä§â§Ú§Ô§Ô§Ö§â, §Ó§ä§à§â§à§Û §ß§Ö§ä
            if (pair.first->isTrigger == pair.second->isTrigger)
                continue;

            auto key = std::make_pair(pair.first, pair.second);
            // §±§â§à§Ó§Ö§â§ñ§Ö§Þ §à§Ò§Ñ §ß§Ñ§á§â§Ñ§Ó§Ý§Ö§ß§Ú§ñ
            bool alreadyEntered = false;
            if (triggersEnteredPair.find(pair.first) != triggersEnteredPair.end() &&
                triggersEnteredPair[pair.first] == pair.second)
                alreadyEntered = true;
            if (triggersEnteredPair.find(pair.second) != triggersEnteredPair.end() &&
                triggersEnteredPair[pair.second] == pair.first)
                alreadyEntered = true;

            if (!alreadyEntered)
            {
                Trigger trigger(pair.first, pair.second);
                pair.first->OnTriggerEnter(trigger);
                pair.second->OnTriggerEnter(trigger);
                triggersEnteredPair[pair.first] = pair.second;   // §ã§à§ç§â§Ñ§ß§ñ§Ö§Þ §Ó §à§Õ§ß§à§Þ §ß§Ñ§á§â§Ñ§Ó§Ý§Ö§ß§Ú§Ú
            }
        }

        // -----------------------------------------------------------------
        // 3. §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §æ§Ú§Ù§Ú§é§Ö§ã§Ü§Ú§ç §Ü§à§Ý§Ý§Ú§Ù§Ú§Û (§â§Ñ§Ù§â§Ö§ê§Ö§ß§Ú§Ö + §ã§à§Ò§í§ä§Ú§ñ)
        // -----------------------------------------------------------------
        for (auto& pair : pairs)
        {
            if (pair.isTrigger) continue;

            bool staticA = pair.first->IsStatic();
            bool staticB = pair.second->IsStatic();
            bool bothDynamic = !staticA && !staticB;

            // §²§Ñ§Ù§â§Ö§ê§Ñ§Ö§Þ §á§â§à§ß§Ú§Ü§ß§à§Ó§Ö§ß§Ú§Ö §ä§à§Ý§î§Ü§à §Ö§ã§Ý§Ú §Ö§ã§ä§î §ã§ä§Ñ§ä§Ú§é§Ö§ã§Ü§Ú§Û §à§Ò§ì§Ö§Ü§ä
            if (!bothDynamic)
            {
                ColliderComponent* staticCol = staticA ? pair.first : pair.second;
                ColliderComponent* dynamicCol = staticA ? pair.second : pair.first;

                auto* dynBody = dynamicCol->GetGameObject()->GetComponent<RigidbodyComponent>();
                if (dynBody && dynBody->GetKinematic())
                    continue;   // §Ü§Ú§ß§Ö§Þ§Ñ§ä§Ú§é§Ö§ã§Ü§Ú§Ö §à§Ò§ì§Ö§Ü§ä§í §ß§Ö §ã§Þ§Ö§ë§Ñ§Ö§Þ

                auto* staticTransform = staticCol->GetGameObject()->GetComponent<TransformComponent>();
                auto* dynamicTransform = dynamicCol->GetGameObject()->GetComponent<TransformComponent>();

                if (staticTransform && dynamicTransform)
                {
                    Vector2Df staticPos = staticTransform->GetWorldPosition();
                    Vector2Df dynamicPos = dynamicTransform->GetWorldPosition();
                    float dx = dynamicPos.x - staticPos.x;
                    float dy = dynamicPos.y - staticPos.y;

                    if (std::abs(pair.intersection.width) < std::abs(pair.intersection.height))
                    {
                        if (dx > 0.f)
                            dynamicTransform->MoveBy({ pair.intersection.width, 0.f });
                        else
                            dynamicTransform->MoveBy({ -pair.intersection.width, 0.f });
                    }
                    else
                    {
                        if (dy > 0.f)
                            dynamicTransform->MoveBy({ 0.f, pair.intersection.height });
                        else
                            dynamicTransform->MoveBy({ 0.f, -pair.intersection.height });
                    }
                }
            }

            // §³§à§Ò§í§ä§Ú§Ö §Ü§à§Ý§Ý§Ú§Ù§Ú§Ú §Ó§í§Ù§í§Ó§Ñ§Ö§ä§ã§ñ §Ó§ã§Ö§Ô§Õ§Ñ
            Collision collision(pair.first, pair.second, pair.intersection);
            pair.first->OnCollision(collision);
            pair.second->OnCollision(collision);
        }

        // -----------------------------------------------------------------
        // 4. §°§Ò§â§Ñ§Ò§à§ä§Ü§Ñ §Ó§í§ç§à§Õ§Ñ §Ú§Ù §ä§â§Ú§Ô§Ô§Ö§â§à§Ó
        // -----------------------------------------------------------------
        for (auto it = triggersEnteredPair.begin(); it != triggersEnteredPair.end(); )
        {
            ColliderComponent* first = it->first;
            ColliderComponent* second = it->second;
            if (!first->bounds.intersects(second->bounds))
            {
                Trigger trigger(first, second);
                first->OnTriggerExit(trigger);
                second->OnTriggerExit(trigger);
                it = triggersEnteredPair.erase(it);
            }
            else
            {
                ++it;
            }
        }
	}*/

	void PhysicsSystem::Update()
	{
		for (int i = 0; i < colliders.size(); i++)
		{
            ColliderComponent* colA = colliders[i];
            RigidbodyComponent* kinematicA = colA->GetGameObject()->GetComponent<RigidbodyComponent>();
            bool staticA = colA->IsStatic();
			if (kinematicA->GetKinematic())
			{
				continue;
			}

			for (int j = 0; j < colliders.size(); j++)
			{
				if (j == i)
				{
					continue;
				}

                ColliderComponent* colB = colliders[j];
                bool staticB = colB->IsStatic();

                // Ïðîïóñêàåì ñòàòè÷åñêèå îáúåêòû
                if (staticA && staticB)
                    continue;

                bool bothDynamic = !staticA && !staticB;

				sf::FloatRect intersection;
				if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
				{
					if (colliders[i]->isTrigger != colliders[j]->isTrigger)
					{
						if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end() && triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
						{
							auto trigger = new Trigger(colliders[i], colliders[j]);
							colliders[i]->OnTriggerEnter(*trigger);
							colliders[j]->OnTriggerEnter(*trigger);

							triggersEnteredPair.emplace(colliders[i], colliders[j]);
						}
					}
					else if (!colliders[i]->isTrigger)
					{
						float intersectionWidth = intersection.width;
						float intersectionHeight = intersection.height;
						Vector2Df intersectionPosition = { intersection.left - 0.5f * intersectionWidth, intersection.top - 0.5f * intersectionHeight };

						Vector2Df aPosition = { colliders[i]->bounds.left,  colliders[i]->bounds.top };
						auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

						if (intersectionWidth > intersectionHeight)
						{
							if (intersectionPosition.y > aPosition.y)
							{
								aTransform->MoveBy({ 0, -intersectionHeight });
								//std::cout << "Top collision" << std::endl;
							}
							else
							{
								aTransform->MoveBy({ 0, intersectionHeight });
								//std::cout << "Down collision" << std::endl;
							}
						}
						else
						{
							if (intersectionPosition.x > aPosition.x)
							{
								aTransform->MoveBy({ -intersectionWidth, 0.f });
								//std::cout << "Right collision" << std::endl;
							}
							else
							{
								aTransform->MoveBy({ intersectionWidth, 0.f });
								//std::cout << "Left collision" << std::endl;
							}
						}

						auto collision = new Collision(colliders[i], colliders[j], intersection);
						colliders[i]->OnCollision(*collision);
						colliders[j]->OnCollision(*collision);
					}
				}
			}
		}

		for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair; triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
		{
			++nextTriggeredPair;
			if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
			{
				auto trigger = new Trigger(triggeredPair->first, triggeredPair->second);
				triggeredPair->first->OnTriggerExit(*trigger);
				triggeredPair->second->OnTriggerExit(*trigger);

				triggersEnteredPair.erase(triggeredPair);
			}
		}
	}

	void PhysicsSystem::Subscribe(ColliderComponent* collider)
	{
		std::cout << "Subscribe " << collider << std::endl;
		colliders.push_back(collider);
		LOG_INFO("Collider subscribed: " + std::to_string((uintptr_t)collider));
	}
	void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
	{
		std::cout << "Unsubscribe " << collider << std::endl;

		colliders.erase(std::remove_if(colliders.begin(), colliders.end(), [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());
	}
}