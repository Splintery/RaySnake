#ifndef ADAPTER_H
#define ADAPTER_H

#include <list>
#include "SFML/Graphics.hpp"
#include "Adaptable.hpp"
#include "../controller/Controller.hpp"

class Adapter {
protected:
    Controller *ctlr;
public:
    Adapter(Controller *);
    virtual ~Adapter();
    virtual std::vector<sf::Drawable *> adapt(Adaptable *) = 0;
};


#endif