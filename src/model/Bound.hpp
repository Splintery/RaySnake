#ifndef BOUND_H
#define BOUND_H

#include "SFML/Graphics.hpp"
#include "Direction.hpp"

class Bound {
private:
public:
    sf::Vector2f topL;
    sf::Vector2f botR;
    Bound(sf::Vector2f, sf::Vector2f);
    Bound(float, float, float, float);
    Bound();
    
    float width() const;
    float height() const;
    void move(sf::Vector2f);
    bool contains(sf::Vector2f);
    bool contains(float, float);

    friend std::ostream &operator<<(std::ostream &, const Bound &);
};

#endif