#include <SFML/Graphics.hpp>
#include "Engine.h"


int main(int argc, char* args[])
{
	// Declare and get ONE instance of a singleton
	Engine& gameEngine = Engine::GetInstance();
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

	// Pass the window reference to the engine and start it
	gameEngine.Start(&window);

	return 0;
}