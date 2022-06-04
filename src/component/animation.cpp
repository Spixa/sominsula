#include "animation.hpp"
#include "entity.hpp"
#include <iostream>

namespace sl {

  Animation::Animation(Entity* entity, sf::String const& textureLoc,sf::Vector2u imageCount,float switchTime) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    
    texture = new sf::Texture();
    flippedTexture = new sf::Texture();
    flippedTextureImage = new sf::Image();

    texture->loadFromFile(textureLoc);
    texture->setRepeated(true);
    flippedTextureImage->loadFromFile(textureLoc);
    flippedTextureImage->flipHorizontally();

    flippedTexture->loadFromImage(*flippedTextureImage);

    animRect.width = texture->getSize().x / float(imageCount.x);
    animRect.height = texture->getSize().y / float(imageCount.y);
    
    entity->getSprite().setTexture(texture);
    this->entity = entity;
  }
  
  void Animation::update(int row,float deltaTime) {

    currentImage.y = row;
    totalTime += deltaTime;
    if (totalTime >= switchTime) {
      totalTime -= switchTime;
      currentImage.x++;
      
      if (currentImage.x >= imageCount.x) {
        currentImage.x = 0;

      }
    }


    animRect.left = currentImage.x * animRect.width;
    animRect.top = currentImage.y * animRect.height;

    sf::IntRect finalr;

    // if (isFacingRight)
      finalr = animRect;
    // else {
    //  finalr = sf::IntRect(animRect.width, 0, -animRect.width, animRect.height);
    // }

    if (isFacingRight)
      entity->getSprite().setTexture(texture);
    else
       entity->getSprite().setTexture(flippedTexture);
    entity->getSprite().setTextureRect(finalr);
  }

  Animation::~Animation() {
    delete texture;
    delete flippedTexture;
    delete flippedTextureImage;
  }

  void Animation::flipTexture() {

    if (isFacingRight) {
      isFacingRight = false;
      return;
    }
    
    isFacingRight = true;

  }

} // namespace axe