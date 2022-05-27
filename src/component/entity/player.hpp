#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../entity.hpp"

namespace sl {
  class Player : public Entity {
    EntityController ec;
    public:
      Player() : Entity(EntityType::PlayerEntityType, "player", 20, 1), ec(this) {
        getSprite().setOrigin({16,16});
        entityAnimations.push_back(new Animation(this, "../res/player/idle.png", {4, 1}, 0.1)); // 0
        entityAnimations.push_back(new Animation(this, "../res/player/walk.png", {6, 1}, 0.1)); // 1
        entityAnimations.push_back(new Animation(this, "../res/player/run.png", {6, 1}, 0.1)); // 2
        entityAnimations.push_back(new Animation(this, "../res/player/attack.png", {6, 1}, 0.1)); // 3

      }

      ~Player() {

      }

      void update(float deltaTime, sf::RenderWindow* window) override {


        window->setView(sf::View(m_sprite.getPosition(), sf::Vector2f(window->getSize())));
        ec.control(deltaTime);

      }

      
  };
}

#endif