#include <iostream>
#include <cmath>
#include <iterator>
#include "SplashState.hpp"
#include "../../settings/Settings.hpp"
#include "../../controller/Controller.hpp"
#include "../../model/Snake.hpp"

State::~State() {
    std::cout << "state destroyed." << std::endl;
}

SplashState::SplashState(Controller *controller): controller{controller} {
	std::cout << "Created SplashState." << std::endl;
}
SplashState::~SplashState() {
  	std::cout << "splashstate destroyed." << std::endl;
}

void SplashState::init() {
    adpater = new SnakeAdapter(controller);
    currentSnake = adpater->adaptSnake(&controller->tmpWorld->getSnake());
}
void SplashState::handleInput() {
	sf::Event event;

	while (controller->window->pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			controller->window->close();
			break;
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                controller->tmpWorld->snake->grow(1);
				// std::cout << gameTitle.getRotation() << std::endl;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                controller->tmpWorld->snake->setDirection(Direction::North);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                controller->tmpWorld->snake->setDirection(Direction::West);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                controller->tmpWorld->snake->setDirection(Direction::South);
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                controller->tmpWorld->snake->setDirection(Direction::East);
            }
			break;
		
		default:
			break;
		}
	}
}

void SplashState::update() {
    currentSnake = adpater->adaptSnake(&controller->tmpWorld->getSnake());
}

void SplashState::drawGrid() {
    sf::RectangleShape line;
    line.setOutlineColor(sf::Color::Red);
    for (int w = 0; w < controller->tmpWorld->getWidth(); w++) {
        line.setPosition(sf::Vector2f(w * TILE_SIZE, 0));
        line.setSize(sf::Vector2f(1.0f, controller->tmpWorld->getHeight() * TILE_SIZE));
        controller->draw(line);
    }

    for (int h = 0; h < controller->tmpWorld->getHeight(); h++) {
        line.setPosition(sf::Vector2f(0, h * TILE_SIZE));
        line.setSize(sf::Vector2f(controller->tmpWorld->getWidth() * TILE_SIZE, 1.0f));
        controller->draw(line);
    }
}

void SplashState::draw() {
	controller->window->clear(sf::Color::Blue);
    drawGrid();

	std::list<sf::Sprite>::iterator it;
	for (it = currentSnake.begin(); it != currentSnake.end(); ++it) {
		// sf::Sprite tmp = *it;
		controller->window->draw(*it);
	}

    controller->window->display();
}