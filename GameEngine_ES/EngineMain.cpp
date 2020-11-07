#include <SFML/Graphics.hpp>
#include "Engine.h"


int main(int argc, char* args[])
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "My Game");

	// run the program as long as the window is open
	while (window.isOpen() == true)
	{
		sf::Event _event;

		// listen to any event occurring while the program is running
		while (window.pollEvent(_event) == true)
		{
			// close requested event
			if (_event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}

	return 0;
}