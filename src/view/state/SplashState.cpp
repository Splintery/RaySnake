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
    drawableSnake = new SnakeAdapter(controller, Direction::East, sf::Vector2f(0, 0), 20);
	an = new AnimatedSprite(controller->resourceManager->getBundle("snake_animated_head").at(0), 16, 4, 0, true, true);
	an->setPosition(200, 200);
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
                drawableSnake->setDirection(Direction::North);
            } else if (Keyboard::isKeyPressed(Keyboard::Q)) {
                drawableSnake->setDirection(Direction::West);
            } else if (Keyboard::isKeyPressed(Keyboard::S)) {
                drawableSnake->setDirection(Direction::South);
            } else if (Keyboard::isKeyPressed(Keyboard::D)) {
                drawableSnake->setDirection(Direction::East);
            } else if (Keyboard::isKeyPressed(Keyboard::Space)) {
				moving = !moving;
            } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				View v = controller->window->getView();
				v.move(0, 10);
				controller->window->setView(v);
			} else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				View v = controller->window->getView();
				v.move(0, -10);
				controller->window->setView(v);
			} else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				View v = controller->window->getView();
				v.move(10, 0);
				controller->window->setView(v);
			} else if (Keyboard::isKeyPressed(Keyboard::Left)) {
				View v = controller->window->getView();
				v.move(-10, 0);
				controller->window->setView(v);
			} else if (Keyboard::isKeyPressed(Keyboard::A)) {
				View v = controller->window->getView();
				v.zoom(0.75f);
				controller->window->setView(v);
			} else if (Keyboard::isKeyPressed(Keyboard::E)) {
				View v = controller->window->getView();
				v.zoom(1.25f);
				controller->window->setView(v);
			}
			break;
		
		default:
			break;
		}
	}
}

void SplashState::update() {
	an->update();
}

void SplashState::draw() {
	// drawableSnake->updateView();
	controller->window->clear(Color::White);

	// Sprite *s = new Sprite(controller->resourceManager->getBundle("snake_body_bundle").at(2));
	// s->setPosition(200, 200);
	// s->setTextureRect(IntRect(0, 0, 300, 16));
	// controller->draw(*s);
	controller->draw(*an);

	controller->draw(*drawableSnake);
    controller->window->display();
}