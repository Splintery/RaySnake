#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>

class AnimatedSprite: public sf::Sprite {
private:
    std::vector<sf::Sprite *> sprites;
    int animationTick = 0;
    int incr = 1;
    sf::Texture &spriteSheet;
    unsigned int animationIndex;
    unsigned int tileSize;
    unsigned int nTextures;
    int animationSpeed; // Numbers of frames per seconds set for the animation
    bool loop;
    bool pingpongLoop;

public:
    // The Texture used to animate will be a grid that will be red from left to right, line by line
    // Incrementing every time by tileSize in order to achieve "animation_fps" numbers of image update
    // every seconds.
    AnimatedSprite(sf::Texture &, unsigned int tileSize, int animation_fps, unsigned int startIndex = 0, bool loop = true, bool pingpongLoop = false);
    virtual ~AnimatedSprite();
    sf::Sprite *getCurrentSprite();
    sf::Sprite * debugMe(int n);
    void setPosition(sf::Vector2f newPos);
    void setPosition(float newX, float newY);
    void update(); // Needs to be called every frame in order to set the correct texture
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif