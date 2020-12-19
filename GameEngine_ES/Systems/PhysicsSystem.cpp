#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
}

PhysicsSystem::~PhysicsSystem()
{
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity,
	float x, float y)
{
	// Check X for collision
	if (touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x)
	{
		// Check Y for collision
		if (touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
			touchedEntity->bottomEdge > touchingEntity->topEdge + y)
		{
			return true;
		}
	}

	return false;
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle,
	float x, float y)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;

	return touchingEntity->rightEdge + x > _touchedRectLeft &&
		_touchedRectRight > touchingEntity->leftEdge + x &&
		touchingEntity->bottomEdge + y > _touchedRectTop &&
		_touchedRectBottom > touchingEntity->topEdge + y;
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	return false;
}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle)
{
}

void PhysicsSystem::CheckCollisionSides(
	ECS::Entity* touchingEntity,
	ECS::Entity* tocuhedEntity)
{
}

void PhysicsSystem::tick(
	ECS::World* world,
	float deltaTime)
{
}
