#include "AnimatedSprite.hpp"


AnimatedSprite::AnimatedSprite(sf::Texture &spriteSheet, int column, int tileSize, int nTextures, int animationSpeed, bool loop, bool reverseLoop): spriteSheet{spriteSheet}, column{column}, tileSize{tileSize}, nTextures{nTextures}, animationSpeed{animationSpeed}, loop{loop}, reverseLoop{reverseLoop} {
    for (unsigned int i = 0; i < spriteSheet.getSize().x; i += tileSize) {
        sf::Sprite *s = new sf::Sprite(spriteSheet, sf::IntRect(i, 0, tileSize, tileSize));
        s->setPosition(200, 200);
        s->setScale(5.0, 5.0);
        sprites.push_back(s);
    }
}

sf::Sprite *AnimatedSprite::getCurrentSprite() {
    return sprites.at(animationIndex);
}

sf::Sprite *AnimatedSprite::debugMe(int n) {
    return sprites.at(n);
}

void AnimatedSprite::update() {
    animationTick++;
    if (animationTick >= animationSpeed) {
        animationTick = 0;
        animationIndex++;
        if (animationIndex >= nTextures && loop) {
            animationIndex = 0;
        }
    }
}


