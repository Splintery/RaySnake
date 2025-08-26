#ifndef ADAPTABLE_H
#define ADAPTABLE_H

#include "../model/Bound.h"
#include "../model/Direction.h"

class Adaptable {
public:
    Adaptable();
    virtual ~Adaptable() = 0;
    virtual std::vector<Bound *> getBounds() = 0;
    virtual std::vector<Direction> getDirections() = 0;
};

#endif