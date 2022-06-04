#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../entity.hpp"

namespace sl {
  class Player : public Entity {
    EntityController ec;
    bool firstTime = true;

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

      void update(float deltaTime, sf::RenderWindow* window, TileMap* map) override {
        sf::View view;

        view.setCenter(m_sprite.getPosition());
        view.setSize(sf::Vector2f(window->getSize()));
        window->setView(view);

        ec.control(deltaTime);
        Tile t = map->setMaterialOfTile(m_sprite.getPosition().x / 32 / map->getScale().x, m_sprite.getPosition().y / 32 / map->getScale().y, 3);
        map->updateTile(t);

        
      }

      
  };
}

#endif