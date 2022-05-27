#include "entity_controller.hpp"
#include "../entity.hpp"
#include <SFML/Window/Keyboard.hpp>

namespace sl {
  EntityController::EntityController(Entity* entity) : entity(entity) {

  }

  void EntityController::control(float deltaTime) {
    bool isRunning{false};
    int updateAnimation{0};
    double speedMultiplier;

    

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
      isRunning = true;
    } else {
      isRunning = false;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      entity->setFaceFlip(true);
      if (isRunning) {   
        updateAnimation = 2;
        speedMultiplier = 2.f;
      } else {
        updateAnimation = 1;
        speedMultiplier = 1.f;
      }

      entity->move(entity->getSpeed() * speedConstant * deltaTime * speedMultiplier, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      
      if (isRunning) {   
        updateAnimation = 2;
        speedMultiplier = 2.f;
      } else {
        updateAnimation = 1;
        speedMultiplier = 1.f;
      }

      entity->move(0, entity->getSpeed() * speedConstant * deltaTime * speedMultiplier);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      if (isRunning) {   
        updateAnimation = 2;
        speedMultiplier = 2.f;
      } else {
        updateAnimation = 1;
        speedMultiplier = 1.f;
      }

      entity->move(0,-(entity->getSpeed() * speedConstant * deltaTime * speedMultiplier));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
       entity->setFaceFlip(false);
      if (isRunning) {   
        updateAnimation = 2;
        speedMultiplier = 2.f;
      } else {
        updateAnimation = 1;
        speedMultiplier = 1.f;
      }

      entity->move(-(entity->getSpeed() * speedConstant * deltaTime * speedMultiplier), 0);
    }

    entity->setCurrentAnimation(updateAnimation);
  }
};