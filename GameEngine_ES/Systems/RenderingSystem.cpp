#include "RenderingSystem.h"

RenderingSystem::RenderingSystem(void)
{
}

RenderingSystem::~RenderingSystem(void)
{
}

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	// Clear before drawing all textures
	Engine::GetInstance().window->clear();
	
	// This is a Lambda (anonymous) function, which allows to pass a function to some function, to be called directly here and nowhere else
	world->each<Transform, Sprite2D>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<Transform> transform,
			ECS::ComponentHandle<Sprite2D> sprite) -> void
		{
			// Add a texture to the map
			if (textureMap.count(sprite->texture) < 1)
			{
				textureMap[sprite->texture] = LoadTexture(sprite->texture);
			}

			// If no texture is found , then add a texture to the map
			if (sprite->sprite.getTexture() == nullptr)
			{
				sprite->sprite.setTexture(*textureMap[sprite->texture]);
				sprite->width = sprite->sprite.getGlobalBounds().width;
				sprite->height = sprite->sprite.getGlobalBounds().height;
			}

			// Update and draw to the screen
			sprite->sprite.setPosition(transform->xPos, transform->yPos);

			Engine::GetInstance().window->draw(sprite->sprite);
		});

	// Display updates
	Engine::GetInstance().window->display();
}

sf::Texture* RenderingSystem::LoadTexture(std::string texturePath)
{
	sf::Texture* _texture = new sf::Texture();

	// if the texture is not found
	if (_texture->loadFromFile(texturePath) == false)
	{
		std::cerr << "Error: Unable to loadimage " << texturePath << ".\nIs this image in the correct directory?" << std::endl;

		system("pause");
		exit(EXIT_FAILURE);
	}

	return _texture;
}
