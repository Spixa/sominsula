#include "realm.hpp"
#include <stdexcept>
#include <iostream>

#include "../component/entity/player.hpp"

namespace sl {
  void Realm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    for (auto X : drawables) {
      target.draw(*X, states);
    }
  }

  Realm::Realm() : map() {
    drawables.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(200, 200)));

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

    map = std::make_shared<TileMap>();
    map->setScale(2, 2);

    if (!map->load("tileset.png", sf::Vector2u(32, 32), level, 16, 8))
        throw std::runtime_error("can't load tileset");

    drawables.push_back(map);

    drawables.push_back(std::make_shared<Player>());
  }

  void Realm::update(float deltaTime, sf::RenderWindow* window) {
    sf::Vector2f hoveringAt = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
  
    
    x = hoveringAt.x / 32;
    y = hoveringAt.y / 32;

    std::cout << "Looking at tile: " << x << " -- " << y << std::endl;

  }

};