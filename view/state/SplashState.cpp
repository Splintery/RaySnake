#include <iostream>
#include "SplashState.hpp"
#include "../../controller/Controller.hpp"

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
	gameTitle.setString("Ray Snake");
    gameTitle.setFont(controller -> resourceManager -> getFont("minecraft"));
    gameTitle.setCharacterSize(26);
    gameTitle.setStyle(sf::Text::Bold);
    sizeIncrement = 1;
}
void SplashState::handleInput() {
	sf::Event event;

	while (controller -> window -> pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			controller -> window -> close();
		}
	}
}
void SplashState::update() {
  	if (gameTitle.getCharacterSize() > 100 || gameTitle.getCharacterSize() < 12) {
    	sizeIncrement *= -1;
  	}
    gameTitle.setCharacterSize(gameTitle.getCharacterSize() + sizeIncrement);
}

void SplashState::draw() {
	controller -> window -> clear();
    controller -> window -> draw(gameTitle);
    controller -> window -> display();
}