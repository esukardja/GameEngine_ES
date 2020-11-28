#include <SFML/Graphics.hpp>
#include "Engine.h"


int main(int argc, char* args[])
{
	// Declare and get ONE instance of a singleton
	Engine& gameEngine = Engine::GetInstance();
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

	// Create the world for attahing entities and systems to
	gameEngine.world = ECS::World::createWorld();

	// Create an entity
	ECS::Entity* stickFigure;

	// Add systems to the engine
	gameEngine.AddSystem(new RenderingSystem());

	// Create and assign 250 entities to the world
	for (int x = 0; x < 25; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			stickFigure = gameEngine.world->create();

			// Assign components to entities after creation
			stickFigure->assign<Transform>(x * 25, y * 25);
			stickFigure->assign<Sprite2D>("../Debug/Pics/hero.png");

			std::cout << stickFigure->getEntityId() << "is the entity ID." << std::endl;
		}
	}

	// Pass the window reference to the engine and start it
	gameEngine.Start(&window);

	return 0;
}