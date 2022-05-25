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
    texture->loadFromFile(textureLoc);

    animRect.width = texture->getSize().x / float(imageCount.x);
    animRect.height = texture->getSize().y / float(imageCount.y);
    
    entity->getSprite().setTexture(*texture);
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

    entity->getSprite().setTexture(*texture);
    entity->getSprite().setTextureRect(animRect);
  }

  Animation::~Animation() {
    // delete texture;
  }

  void Animation::flipTexture() {

    if (isFacingRight) {
      isFacingRight = false;
      return;
    }
    
    isFacingRight = true;

  }

} // namespace axe