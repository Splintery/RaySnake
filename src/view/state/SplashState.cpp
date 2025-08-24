#include <iostream>
#include <cmath>
#include <iterator>
#include "SplashState.hpp"
#include "../../settings/Settings.hpp"
#include "../../controller/Controller.hpp"
#include "../../model/snake/Snake.hpp"
#include <optional>

// using namespace sf;

SplashState::SplashState(Controller *controller): State{}, controller{controller} {
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
	while (controller->window->isOpen()) {
		while (const std::optional event = controller->window->pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				controller->window->close();
			} else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
				switch (keyPressed->scancode)
				{
				case sf::Keyboard::Scancode::Z:
					snake->setDirection(Direction::North);
					break;
				case sf::Keyboard::Scancode::Q:
					snake->setDirection(Direction::West);
					break;
				case sf::Keyboard::Scancode::S:
					snake->setDirection(Direction::South);
					break;
				case sf::Keyboard::Scancode::D:
					snake->setDirection(Direction::East);
					break;
				case sf::Keyboard::Scancode::Up: {
					sf::View v = controller->window->getView();
					v.move({0, 10});
					controller->window->setView(v);
					break;
				}
				case sf::Keyboard::Scancode::Down: {
					sf::View v = controller->window->getView();
					v.move({0, -10});
					controller->window->setView(v);
					break;
				}
				case sf::Keyboard::Scancode::Right: {
					sf::View v = controller->window->getView();
					v.move({10, 0});
					controller->window->setView(v);
					break;
				}
				case sf::Keyboard::Scancode::Left: {
					sf::View v = controller->window->getView();
					v.move({-10, 0});
					controller->window->setView(v);
					break;
				}
				case sf::Keyboard::Scancode::A: {
					sf::View v = controller->window->getView();
					v.zoom(0.75f);
					controller->window->setView(v);
					break;
				}
				case sf::Keyboard::Scancode::E: {
					sf::View v = controller->window->getView();
					v.zoom(1.25f);
					controller->window->setView(v);
					break;
				}
				default:
					break;
				}
				if (keyPressed->scancode == sf::Keyboard::Scancode::Z)
				{

				}
			}
		}
	}
}

void SplashState::update() {
	// if (moving) {snake->update();drawableSnake->update();}
}

void SplashState::draw() {
	controller->window->clear(sf::Color::White);

    // an->update();
    // controller->draw(*an);
	sf::Sprite *s = new sf::Sprite(controller->resourceManager->getBundle("snake_tail_bundle").at(0));
	s->setPosition({200, 200});
	controller->draw(*s);

	controller->draw(*drawableSnake);
	// std::vector<Drawable *>::iterator it;
	// for (it = currentSpriteSnake.begin(); it != currentSpriteSnake.end(); ++it) {
	// 	Drawable *tmp = *it;
	// 	controller->window->draw(*tmp);
	// }

    controller->window->display();
}