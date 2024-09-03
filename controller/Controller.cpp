#include <iostream>
#include "Controller.hpp"

Controller::Controller(int width, int height, const std::string &title) {
    std::cout << "Creating controller..." << std::endl;

    window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window -> isOpen())
    {
        sf::Event event;
        while (window -> pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window -> close();
        }

        window -> clear();
        window -> draw(shape);
        window -> display();
    }

}
