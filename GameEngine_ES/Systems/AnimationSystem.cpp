#include "AnimationSystem.h"

AnimationSystem::AnimationSystem(void)
{
}

AnimationSystem::~AnimationSystem(void)
{
}

void AnimationSystem::tick(ECS::World* world, float deltaTime)
{
	world->each<Animator, Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Animator> animator,
			ECS::ComponentHandle<Sprite2D> sprite) -> void
		{
			// set the timer for the animator
			animator->currentTime += deltaTime;

			// set animation forward and reset at the first frame to loop it
			if (animator->currentTime >= animator->nextTimeFrame)
			{
				animator->currentTime = 0;

				// run through the animation spritesheet regardless of rows and columns
				animator->currentColumn = (animator->currentColumn + 1) % animator->totalColumns;
			}
			
			sprite->sprite.setTextureRect(
				sf::IntRect(
					animator->currentColumn * animator->frameWidth,
					animator->currentRow * animator->frameHeight,
					animator->frameWidth,
					animator->frameHeight));
		});
}