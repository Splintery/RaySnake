#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <vector>
#include <SFML/Graphics.hpp>

class AnimatedSprite: public sf::Drawable {
private:
    std::vector<sf::Sprite *> sprites;
    int animationTick = 0;
    int animationIndex = 0;
    sf::Texture &spriteSheet;
    int column;
    int tileSize;
    int nTextures;
    int animationSpeed; // Numbers of frames per seconds set for the animation
    bool loop;
    bool reverseLoop;

public:
    // The Texture used to animate will be a grid that will be red from left to right, line by line
    // Incrementing every time by tileSize in order to achieve "animation_fps" numbers of image update
    // every seconds.
    AnimatedSprite(sf::Texture &, int column, int tileSize, int nTextures, int animation_fps, bool loop = true, bool reverseLoop = false);
    sf::Sprite *getCurrentSprite();
    sf::Sprite * debugMe(int n);
    void update(); // Needs to be called every frame in order to set the correct texture
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif