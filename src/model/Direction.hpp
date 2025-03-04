#ifndef DIRECTION_H
#define DIRECTION_H

#include <SFML/Graphics.hpp>
#include "Bound.hpp"

class Direction {
public:
    enum Value {
        North = 1,
        South = -1,
        East = -2,
        West = 2
    };
    Direction() = default;
    Direction(Value);
    Direction(int);
    Direction invert();
    operator Value() const;
    explicit operator bool() const = delete;
    bool operator==(Direction d) const;
    bool operator==(Direction::Value) const;
    bool operator!=(Direction d) const;
    bool operator!=(Direction::Value) const;
    int toIndex() const;
    int indexTowards(Direction) const;

    static sf::Vector2f getVectorTowards(Direction, sf::Vector2f, float);
    // Creates a new Bound from the one passed as argument by moving both
    // its points towards the desired direction by an amount 
    static Bound *getBoundTowards(Direction, Bound *, float);
    // Creates a new Bound from the one passed as argument by moving only one of
    // its points towards the desired direction by an amount 
    static Bound *getStretchedBoundTowards(Direction, Bound *, float);

    friend std::ostream &operator<<(std::ostream &, const Direction &);

private:
    Value value;
};
// static sf::Vector2f &operator*(const sf::Vector2f &, const sf::Vector2f &);

#endif