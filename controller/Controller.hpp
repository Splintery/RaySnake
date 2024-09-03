#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SFML/Graphics.hpp>

class Controller {
      private:
            sf::RenderWindow* window;
      public:
            Controller(int width, int height, const std::string &title);
};

#endif