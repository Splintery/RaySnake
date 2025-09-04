#ifndef BOUND_H
#define BOUND_H

#include <SFML/System/Vector2.hpp>
#include <ostream>

class Bound {
public:
    sf::Vector2<float> topL;
    sf::Vector2<float> botR;
    Bound(sf::Vector2<float>, sf::Vector2<float>);
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
    bool contains(sf::Vector2<float>);
    bool contains(float, float);

    // Bound &operator=(const Bound&) = default;
    friend std::ostream &operator<<(std::ostream &, const Bound &);
};

#endif