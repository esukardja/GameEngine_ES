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
	ECS::ComponentHandle<BoxCollider> touchingBox,
	ECS::ComponentHandle<BoxCollider> touchedBox)
{
	return touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge &&
		touchingBox->bottomEdge > touchedBox->topEdge &&
		touchedBox->bottomEdge > touchingBox->topEdge;
}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	// Scenario dealing with collision from the right side by accelerating rightward
	if (transform->xSpeed > 0 &&
		touchingEntity->rightEdge + transform->xSpeed > touchedEntity->leftEdge &&
		touchedEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward

	if (transform->ySpeed > 0 &&
		touchingEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
		touchedEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (transform->xSpeed < 0 &&
		touchingEntity->leftEdge + transform->xSpeed < touchedEntity->rightEdge &&
		touchedEntity->topEdge < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward

	if (transform->ySpeed > 0 &&
		touchingEntity->topEdge + transform->ySpeed < touchedEntity->bottomEdge &&
		touchedEntity->leftEdge < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge)
	{
		transform->ySpeed = 0;
	}

}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle)
{
	float _touchedRectLeft = touchedRectangle.getPosition().x;
	float _touchedRectRight = touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;

	// Scenario dealing with collision from the right side by accelerating rightward
	if (transform->xSpeed > 0 &&
		touchingEntity->rightEdge + transform->xSpeed > _touchedRectLeft &&
		touchingEntity->topEdge <_touchedRectBottom &&
		touchingEntity->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward

	if (transform->ySpeed > 0 &&
		touchingEntity->bottomEdge + transform->ySpeed > _touchedRectTop &&
		touchingEntity->leftEdge < _touchedRectRight &&
		touchingEntity->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (transform->xSpeed < 0 &&
		touchingEntity->leftEdge + transform->xSpeed < _touchedRectRight &&
		touchingEntity->topEdge <_touchedRectBottom &&
		touchingEntity->bottomEdge > _touchedRectTop)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward

	if (transform->ySpeed > 0 &&
		touchingEntity->topEdge + transform->ySpeed < _touchedRectBottom &&
		touchingEntity->leftEdge < _touchedRectRight &&
		touchingEntity->rightEdge > _touchedRectLeft)
	{
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(
	ECS::Entity* touchingEntity,
	ECS::Entity* touchedEntity)
{
	ECS::ComponentHandle<Transform> _touchingTransform = touchingEntity->get<Transform>();
	ECS::ComponentHandle<Transform> _touchedTransform = touchedEntity->get<Transform>();

	if ((_touchingTransform->xPos - _touchingTransform->xSpeed) < (_touchedTransform->xPos - _touchingTransform->xSpeed))
	{
		_touchedTransform->xPos++;
	}

	else if ((_touchingTransform->xPos - _touchingTransform->xSpeed) > (_touchedTransform->xPos - _touchingTransform->xSpeed))
	{
		_touchedTransform->xPos--;
	}

	else if ((_touchingTransform->yPos - _touchingTransform->ySpeed) < (_touchedTransform->yPos - _touchingTransform->ySpeed))
	{
		_touchedTransform->yPos++;
	}

	else if ((_touchingTransform->yPos - _touchingTransform->ySpeed) > (_touchedTransform->yPos - _touchingTransform->ySpeed))
	{
		_touchedTransform->yPos--;
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<BoxCollider, Sprite2D, Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<BoxCollider> box,
			ECS::ComponentHandle<Sprite2D> sprite,
			ECS::ComponentHandle<Transform> transform
		) -> void
	{
		box->Update(transform->xPos, transform->yPos,
			sprite->sprite.getTextureRect().width,
			sprite->sprite.getTextureRect().height);
	});

	world->each<BoxCollider, Transform>(
		[&](ECS::Entity* touchingEntity,
			ECS::ComponentHandle<BoxCollider> touchingBox,
			ECS::ComponentHandle<Transform> transform1) -> void
	{
			world->each<BoxCollider, Transform>(
				[&](ECS::Entity* touchedEntity,
					ECS::ComponentHandle<BoxCollider> touchedBox,
					ECS::ComponentHandle<Transform> transform2) -> void
				{
					// statement to avoid comparing same entity to itelf
					if (touchingEntity->getEntityId() != touchedEntity->getEntityId())
					{
						// initial collision check
						if (IsColliding(touchingBox, touchedBox) == true)
						{
							// final collision check
							CheckCollisionSides(touchingEntity, touchedEntity);
						}
					}
				});
	});

	world->each<Transform>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Transform> transform
			) -> void
		{
			transform->Move();
		});
}
