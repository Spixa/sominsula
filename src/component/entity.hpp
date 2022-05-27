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
      sf::RectangleShape m_sprite{sf::Vector2f(32,32)};
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

      sf::RectangleShape& getSprite() { return m_sprite; }
      std::string getName() const { return name; }
      EntityType getType() const { return type; }
      double getSpeed() const { return speed; }
      double getHp() const { return hp; }

      void setName(std::string const& name) { this->name = name; }
      void setType(EntityType const& type) { this->type = type; }
      void setSpeed(double speed) { this->speed = speed; }
      void setHp(double hp) { this->hp = hp; }
      void setCurrentAnimation(unsigned int t) { currentAnimation = t; }
      void setFaceFlip(bool right) {
        entityAnimations[currentAnimation]->isFacingRight = right;
      }

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
      

        update(deltaTime, window);
      }
  };
}

#endif