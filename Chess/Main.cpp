#include <SFML/Graphics.hpp>
//#include <time.h>

using namespace sf;

int main()
{
	
	RenderWindow window(VideoMode(453, 453), "chess");

	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		window.display();
	}
	return 0;
}