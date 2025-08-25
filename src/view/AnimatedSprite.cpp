#include "AnimatedSprite.hpp"


AnimatedSprite::AnimatedSprite(sf::Texture &spriteSheet, unsigned int tileSize, int animationSpeed, unsigned int startIndex, bool loop, bool pingpongLoop): sf::Sprite{spriteSheet}, spriteSheet{spriteSheet}, animationIndex{startIndex}, tileSize{tileSize}, nTextures{spriteSheet.getSize().x / tileSize}, animationSpeed{animationSpeed}, loop{loop}, pingpongLoop{pingpongLoop} {
    for (int i = 0; i < spriteSheet.getSize().x; i += tileSize) {
        sf::Sprite *s = new sf::Sprite(spriteSheet, sf::IntRect({i, 0}, {tileSize, tileSize}));
        sprites.push_back(s);
    }
}

AnimatedSprite::~AnimatedSprite() {
    while (!sprites.empty()) {
        sprites.pop_back();
    } 
}

sf::Sprite *AnimatedSprite::getCurrentSprite() {
    return sprites.at(animationIndex);
}

sf::Sprite *AnimatedSprite::debugMe(int n) {
    return sprites.at(n);
}

void AnimatedSprite::setPosition(sf::Vector2f newPos) {
    for (Sprite *s : sprites) {
        s->setPosition(newPos);
    }
}

void AnimatedSprite::setPosition(float newX, float newY) {
    setPosition(sf::Vector2f(newX, newY));
}

void AnimatedSprite::update() {
    animationTick++;
    if (animationTick >= animationSpeed) {
        animationTick = 0;
        animationIndex += incr;
        if (loop && (animationIndex == nTextures || animationIndex < 0)) {
            incr = pingpongLoop ? -incr : incr;
            animationIndex = incr == 1 ? 0 : nTextures - 1;
        }
    }
}

void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*sprites.at(animationIndex), states);
}
