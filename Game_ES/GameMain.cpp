#include "../GameEngine_ES/Engine.h"


int main(int argc, char* args[])
{
	// Declare and get ONE instance of a singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

	// Create the world for attahing entities and systems to
	gameEngine.world = ECS::World::createWorld();

	// Create 3 entities
	ECS::Entity* background;
	ECS::Entity* stickFigure;
	ECS::Entity* tux;

	// Add systems to the engine
	gameEngine.AddSystem(new RenderingSystem());
	gameEngine.AddSystem(new AnimationSystem());
	gameEngine.AddSystem(new InputSystem(&window));
	gameEngine.AddSystem(new MovementSystem());
	gameEngine.AddSystem(new PhysicsSystem());

	// Create 3 entities to the world
	background = gameEngine.world->create();
	stickFigure = gameEngine.world->create();
	tux = gameEngine.world->create();

	// Assign components to entities after creation
	background->assign<struct Transform>(0, 0, 0, 0);
	background->assign<struct Sprite2D>("../Debug/Pics/bg.jpg");

	stickFigure->assign<struct Transform>(300, 300, 0.2f, 0.2f);
	stickFigure->assign<struct Sprite2D>("../Debug/Pics/herosheet.png");
	stickFigure->assign<struct Animator>(32, 32, 400.0f, 4, 1);
	stickFigure->assign<struct BoxCollider>();

	tux->assign<struct Transform>(200, 200, 0.6f, 0.6f);
	tux->assign<struct Sprite2D>("../Debug/Pics/tux_from_linux.png");
	tux->assign<struct Animator>(56, 72, 250.0f, 3, 9);
	tux->get<struct Animator>()->currentRow = 0; // idle row
	tux->assign<struct InputController>();
	tux->assign<struct BoxCollider>();
	tux->assign<struct Camera>(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));

	std::cout << background->getEntityId() << "is the entity ID." << std::endl;
	std::cout << stickFigure->getEntityId() << "is the entity ID." << std::endl;
	std::cout << tux->getEntityId() << "is the entity ID." << std::endl;

	// Pass the window reference to the engine and start it
	gameEngine.Start(&window);

	return 0;
}