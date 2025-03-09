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
	snake = new Snake(Direction::East, sf::Vector2f(0, 0), 20);
    drawableSnake = new SnakeAdapter(controller, snake);
    // an = new AnimatedSprite(controller->resourceManager->getTexture("testAni"), 7, 16, 7, 14);
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
                snake->setDirection(Direction::North);
            } else if (Keyboard::isKeyPressed(Keyboard::Q)) {
                snake->setDirection(Direction::West);
            } else if (Keyboard::isKeyPressed(Keyboard::S)) {
                snake->setDirection(Direction::South);
            } else if (Keyboard::isKeyPressed(Keyboard::D)) {
                snake->setDirection(Direction::East);
            } else if (Keyboard::isKeyPressed(Keyboard::Space)) {
				moving = !moving;
            }
			else if (Keyboard::isKeyPressed(Keyboard::Up)) {
				View v = controller->window->getView();
				v.move(0, 10);
				controller->window->setView(v);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Down)) {
				View v = controller->window->getView();
				v.move(0, -10);
				controller->window->setView(v);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Right)) {
				View v = controller->window->getView();
				v.move(10, 0);
				controller->window->setView(v);
			}
			else if (Keyboard::isKeyPressed(Keyboard::Left)) {
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
	// if (moving) {snake->update();drawableSnake->update();}
}

void SplashState::draw() {
	controller->window->clear(Color::White);

    // an->update();
    // controller->draw(*an);
	Sprite *s = new Sprite(controller->resourceManager->getBundle("snake_tail_bundle").at(0));
	s->setPosition(200, 200);
	controller->draw(*s);

	controller->draw(*drawableSnake);
	// std::vector<Drawable *>::iterator it;
	// for (it = currentSpriteSnake.begin(); it != currentSpriteSnake.end(); ++it) {
	// 	Drawable *tmp = *it;
	// 	controller->window->draw(*tmp);
	// }

    controller->window->display();
}