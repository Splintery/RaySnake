#ifndef ADAPTER_H
#define ADAPTER_H

#include <list>
#include "SFML/Graphics.hpp"
#include "Adaptable.h"
#include "../controller/Controller.h"

//TODO: Make this class extends sf::Drawable make it so that the draw function also updates animated sprites
class Adapter: public sf::Drawable {
protected:
    Controller *ctrl;
    Adaptable *adaptable;
public:
    Adapter(Controller *, Adaptable *);
    virtual ~Adapter();
    // virtual std::vector<sf::Drawable *> adapt(Adaptable *) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};


#endif