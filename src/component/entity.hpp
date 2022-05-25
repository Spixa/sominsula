#include <SFML/Graphics.hpp>
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics/Transformable.hpp>
#include "entity_types.hpp"

namespace sl {

  class Entity : public sf::Drawable, public sf::Transformable{
      sf::Sprite m_sprite;
      sf::Texture m_texture;
      EntityType type;
      std::string name;
      double hp;
      double speed;

    public:
      Entity(EntityType type, std::string const& name, double hp, double speed);
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

      virtual ~Entity() {}

      std::string getName() const { return name; }
      EntityType getType() const { return type; }
      double getSpeed() const { return speed; }
      double getHp() const { return hp; }

      void setName(std::string const& name) { this->name = name; }
      void setType(EntityType const& type) { this->type = type; }
      void setSpeed(double speed) { this->speed = speed; }
      void setHp(double hp) { this->hp = hp; }

      virtual void update(float deltaTime, sf::RenderWindow* window) = 0;

  };
}

#endif