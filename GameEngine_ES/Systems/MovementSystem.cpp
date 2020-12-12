#include "MovementSystem.h"

#define X_SPEED 0.3
#define Y_SPEED 0.3

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<InputController, Transform, Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Animator> animator) -> void
	{
		if (input->bInputActive == true)
		{
			if (input->wKey == true)
			{
				transform->ySpeed = -Y_SPEED;
				transform->Move();
			}
			else if (input->sKey == true)
			{
				transform->ySpeed = Y_SPEED;
				transform->Move();
			}
			else
			{
				transform->ySpeed = 0;
				transform->Move();
			}

			if (input->aKey == true)
			{
				animator->bIsFacingRight = false;
				animator->currentRow = 1;
				transform->xSpeed = -X_SPEED;
				transform->Move();
			}

			else if (input->dKey == true)
			{
				animator->bIsFacingRight = true;
				animator->currentRow = 1;
				transform->xSpeed = X_SPEED;
				transform->Move();
			}

			else
			{
				animator->currentRow = 0;
				transform->xSpeed = 0;
			}
		}
	});
}
