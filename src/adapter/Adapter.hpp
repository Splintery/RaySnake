#ifndef ADAPTER_H
#define ADAPTER_H

#include <list>
#include "SFML/Graphics.hpp"
#include "../controller/Controller.hpp"

//TODO: Make this class extends sf::Drawable make it so that the draw function also updates animated sprites
class Adapter: public sf::Drawable {
protected:
    Controller *ctrl;
public:
    Adapter(Controller *);
    virtual ~Adapter();
    virtual void updateView() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


#endif