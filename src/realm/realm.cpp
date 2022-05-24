#include "realm.hpp"

namespace sl {
  void Realm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    for (auto x : drawables) {
      target.draw(*x, states);
    }
  }

  Realm::Realm() {
    drawables.push_back(std::make_shared<sf::RectangleShape>(sf::Vector2f(200, 200)));
  }

};