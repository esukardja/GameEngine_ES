#include "MovementSystem.h"

//#define X_SPEED 0.3
//#define Y_SPEED 0.3

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<struct InputController, struct Transform, struct Animator>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<struct InputController> input,
			ECS::ComponentHandle<struct Transform> transform,
			ECS::ComponentHandle<struct Animator> animator) -> void
	{
		if (input->bInputActive == true)
		{
			if (input->wKey == true)
			{
				transform->ySpeed = -transform->ySpeedMod;
				transform->Move();
			}
			else if (input->sKey == true)
			{
				transform->ySpeed = transform->ySpeedMod;
				transform->Move();
			}
			else
			{
				transform->ySpeed = 0;
			}

			if (input->aKey == true)
			{
				animator->bIsFacingRight = false;
				animator->currentRow = 1;
				transform->xSpeed = -transform->xSpeedMod;
				transform->Move();
			}

			else if (input->dKey == true)
			{
				animator->bIsFacingRight = true;
				animator->currentRow = 1;
				transform->xSpeed = transform->xSpeedMod;
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
