#pragma once

#include "../Engine.h"


class PhysicsSystem : public ECS::EntitySystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();

	bool IsColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity,
		float x, float y
	);

	bool IsColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		sf::RectangleShape touchedRectangle,
		float x, float y
	);

	bool IsColliding(
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity
	);

	void CheckCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider>  touchingEntity,
		ECS::ComponentHandle<BoxCollider> touchedEntity
	);

	void CheckCollisionSides(
		ECS::ComponentHandle<Transform> transform,
		ECS::ComponentHandle<BoxCollider> touchingEntity,
		sf::RectangleShape touchedRectangle
	);

	void CheckCollisionSides(
		ECS::Entity* touchingEntity,
		ECS::Entity* tocuhedEntity
	);

	void tick(ECS::World* world, float deltaTime) override;
};

