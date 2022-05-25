#include <SFML/Graphics.hpp>
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Transformable.hpp>
#include "entity_types.hpp"
#include "animation.hpp"
#include "tilemap.hpp"
#include "io/entity_controller.hpp"

#include <vector>

#include <iostream>

namespace sl {

  class Entity : public sf::Drawable, public sf::Transformable{
    protected:
      sf::Sprite m_sprite;
      sf::Texture m_texture;

      std::vector<Animation*> entityAnimations;
      unsigned int currentAnimation{0};

    private:
      EntityType type;
      std::string name;
      double hp;
      double speed;
      sf::Vector2i position;

    public:
      Entity(EntityType type, std::string const& name, double hp, double speed);
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

      virtual ~Entity() {
        for (auto x : entityAnimations) {
          delete x;
        }
        entityAnimations.clear();
      }

      sf::Sprite& getSprite() { return m_sprite; }
      std::string getName() const { return name; }
      EntityType getType() const { return type; }
      double getSpeed() const { return speed; }
      double getHp() const { return hp; }

      void setName(std::string const& name) { this->name = name; }
      void setType(EntityType const& type) { this->type = type; }
      void setSpeed(double speed) { this->speed = speed; }
      void setHp(double hp) { this->hp = hp; }
      void setCurrentAnimation(unsigned int t) { currentAnimation = t; }

      void move(sf::Vector2f pos) { 
        m_sprite.move(sf::Vector2f(pos));
      }

      void move(float x, float y) { 
        m_sprite.move(sf::Vector2f(x, y));
      }

      virtual void update(float deltaTime, sf::RenderWindow* window) = 0;
      void update_entity(float deltaTime, sf::RenderWindow* window, TileMap* map) {
        if (!entityAnimations.empty() && entityAnimations[currentAnimation])
          entityAnimations[currentAnimation]->update(0, deltaTime);
        
        int x = m_sprite.getPosition().x / 32 / map->getScale().x;
        int y = m_sprite.getPosition().y / 32 / map->getScale().y;

        std::cout << "Standing at tile: " << x << " -- " << y << std::endl;

        update(deltaTime, window);
      }
  };
}

#endif