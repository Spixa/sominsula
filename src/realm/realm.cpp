#include "realm.hpp"
#include <stdexcept>
#include <iostream>

#include "../component/entity/player.hpp"

namespace sl {
  void Realm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    target.draw(*map.get());

    for (auto X : entities) {
      target.draw(*X, states);
    }

  }

  Realm::Realm() : map(std::make_shared<TileMap>()) {

    const int level[] =
    {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
        1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
        0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
        0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
        0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
        2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
        0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
    };  

    map->setScale(2, 2);

    if (!map->load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
        throw std::runtime_error("can't load tileset");

    entities.push_back(std::make_shared<Player>());
  }

  void Realm::update(float deltaTime, sf::RenderWindow* window) {
    for (auto X : entities) {
      X->update_entity(deltaTime, window, map.get());
    }

  }

};