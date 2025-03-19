#ifndef SNAKEADAPTER_H
#define SNAKEADAPTER_H

#include "Adapter.hpp"
#include "../view/AnimatedSprite.hpp"
#include "../model/Snake.hpp"

//TODO: Rethink class as to "re-use" the previous adapted snake to produce the new one,
//make it work seemlessly with custom AnimatedSprite.hpp
class SnakeAdapter: public Adapter , public Snake {
private:
    std::vector<AnimatedSprite *> sprites;
public:
    SnakeAdapter(Controller *, const Direction &, sf::Vector2f, float);
    virtual void updateView();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update() override;
    void grow(float) override;
    void move(float) override;
};

#endif