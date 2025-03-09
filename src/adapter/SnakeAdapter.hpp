#ifndef SNAKEADAPTER_H
#define SNAKEADAPTER_H

#include "Adapter.hpp"
#include "../view/AnimatedSprite.hpp"
#include "../model/Snake.hpp"

//TODO: Rethink class as to "re-use" the previous adapted snake to produce the new one,
//make it work seemlessly with custom AnimatedSprite.hpp
class SnakeAdapter: public Adapter {
private:
    std::vector<sf::Drawable *> sprites;
    std::vector<AnimatedSprite *> aniSprites;
    sf::Texture &getCurvedBodyTexture(std::vector<Direction> &dirs, int i);
    sf::Texture &findTexture(std::vector<Bound *> &bounds, std::vector<Direction> &dirs, int i, float j);
    sf::Sprite *buildSprite(SnakePart *, float i);
public:
    SnakeAdapter(Controller *, Adaptable *);
    
    // std::vector<sf::Drawable *> adapt(Adaptable *);
    virtual void update();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif