#include "AnimatedSprite.hpp"


AnimatedSprite::AnimatedSprite(sf::Texture &spriteSheet, unsigned int tileSize, int animationSpeed, unsigned int startIndex, bool loop, bool pingpongLoop): spriteSheet{spriteSheet}, animationIndex{startIndex}, tileSize{tileSize}, nTextures{spriteSheet.getSize().x / tileSize}, animationSpeed{animationSpeed}, loop{loop}, pingpongLoop{pingpongLoop} {
    sf::Image img = spriteSheet.copyToImage();
    for (unsigned int i = 0; i < spriteSheet.getSize().x; i += tileSize) {
        sf::Texture t;
        t.loadFromImage(img, sf::IntRect(i, 0, tileSize, tileSize));
        textures.push_back(t);
    }
    this->setTexture(textures.at(0));
}

AnimatedSprite::~AnimatedSprite() {
    while (!textures.empty()) {
        textures.pop_back();
    } 
}

sf::Texture &AnimatedSprite::getCurrentSprite() {
    return textures.at(animationIndex);
}

sf::Texture &AnimatedSprite::debugMe(int n) {
    return textures.at(n);
}

bool canIncr(int animationIndex, int incr, int nTextures) {
    return (incr == 1 && animationIndex >= 0 && animationIndex < nTextures-1)
    || (incr == -1 && animationIndex > 0 && animationIndex < nTextures);
}

void AnimatedSprite::update() {
    animationTick++;
    if (animationTick >= animationSpeed) {
        animationTick = 0;
        if (canIncr(animationIndex, incr, nTextures)) {
            animationIndex += incr;
        } else if (loop) {
            incr = (pingpongLoop) ? -incr : incr;
            animationIndex = (incr == 1) ? 0 : nTextures - 1;
        }
        setTexture(textures.at(animationIndex));
    }    
}

// void AnimatedSprite::draw(sf::RenderTarget &target, sf::RenderStates states) const {
//     target.draw(*this, states);
// }
