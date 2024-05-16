#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "System.h"
#include "Component.h"

int main()
{
    sf::Vector2f p(100, 200), v(10, 10);
    eBall ball;
    ball.cTransform = std::make_shared<cTransform>(p, v);
    ball.cShape = std::make_shared<cShape>(p);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}