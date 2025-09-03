#ifndef ADAPTABLE_H
#define ADAPTABLE_H

#include "../model/tools/Bound.h"
#include "../model/tools/Direction.h"

class Adaptable {
public:
    Adaptable();
    virtual ~Adaptable() = 0;
    virtual std::vector<Bound> getBounds() = 0;
    virtual std::vector<Direction> getDirections() = 0;
};

#endif