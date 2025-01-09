#ifndef BOUND_H
#define BOUND_H

#include "SFML/Graphics.hpp"

class Bound {
public:
    const sf::Vector2f topL;
    const sf::Vector2f botR;
    Bound(sf::Vector2f, sf::Vector2f);
    Bound(float, float, float, float);
    Bound();
    virtual ~Bound();
    Bound(const Bound &);
    // Allows us to create a Bound of surface 1²(width=1, height=1) from either point of the Bound
    // Exemple: Bound given -> tl(0, 1); br(5, 0) and fromTl=true -> Bound res tl(0, 1); br(1, 0)
    // same exemple with fromTl=false -> Bound res tl(4, 1); br(5, 0).
    Bound(Bound *, bool fromTl);
    
    float width() const;
    float height() const;
    bool contains(sf::Vector2f);
    bool contains(float, float);

    friend std::ostream &operator<<(std::ostream &, const Bound &);
};

#endif