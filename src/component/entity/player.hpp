#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../entity.hpp"

namespace sl {
  class Player : public Entity {
    
    public:
      explicit Player(std::string const& name) : Entity(EntityType::PlayerEntityType, name, 20, 1) {

      }

      Player() : Entity(EntityType::PlayerEntityType, "player", 20, 1) {

      }

      ~Player() {

      }

      void update(float deltaTime, sf::RenderWindow* window) override {

      }

      
  };
}

#endif