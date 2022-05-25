#include "entity.hpp"

namespace sl {
  Entity::Entity(EntityType type, std::string const& name, double hp, double speed) : 
    type(type), name(name), hp(hp), speed(speed)
  {
    std::string path;
    if (type == EntityType::PlayerEntityType) {
      path = "../res/player/player.png";
    }

    m_texture.loadFromFile(path);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale({1.5, 1.5});

  }

  void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = &m_texture;

    // you may also override states.shader or states.blendMode if you want

    // draw the vertex array
    target.draw(m_sprite, states);
  }
};