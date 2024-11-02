#include <iostream>
#include <cmath>
#include <iterator>
#include "SplashState.hpp"
#include "../../settings/Settings.hpp"
#include "../../controller/Controller.hpp"
#include "../../model/Snake.hpp"

using namespace sf;

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
    adpater = new SnakeOptAdapter(controller);
    currentSnake = adpater->adapt(&controller->world->getSnake());
    an = new AnimatedSprite(controller->resourceManager->getTexture("testAni"), 7, 16, 7, 14);
}
void SplashState::handleInput() {
	Event event;

	while (controller->window->pollEvent(event)) {
		switch (event.type)
		{
		case Event::Closed:
			controller->window->close();
			break;
		case Event::KeyPressed:
			if (Keyboard::isKeyPressed(Keyboard::Z)) {
                controller->world->snake->setDirection(Direction::North);
            } else if (Keyboard::isKeyPressed(Keyboard::Q)) {
                controller->world->snake->setDirection(Direction::West);
            } else if (Keyboard::isKeyPressed(Keyboard::S)) {
                controller->world->snake->setDirection(Direction::South);
            } else if (Keyboard::isKeyPressed(Keyboard::D)) {
                controller->world->snake->setDirection(Direction::East);
            } else if (Keyboard::isKeyPressed(Keyboard::Space)) {
                // controller->moveTmp();
				controller->world->snake->grow(10.0);
            }
			break;
		
		default:
			break;
		}
	}
}

void SplashState::update() {
    currentSnake = adpater->adapt(&controller->world->getSnake());
}

void SplashState::draw() {
	controller->window->clear(Color::Blue);

    // controller->window->draw(*an->debugMe(0));
    // an->update();
    // controller->draw(*an->getCurrentSprite());


	std::vector<Drawable *>::iterator it;
	for (it = currentSnake.begin(); it != currentSnake.end(); ++it) {
		// Sprite tmp = *it;
		controller->window->draw(**it);
	}

    controller->window->display();
}