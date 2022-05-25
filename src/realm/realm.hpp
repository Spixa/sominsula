#ifndef REALM_HPP
#define REALM_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../component/tilemap.hpp"

namespace sl {
  class Realm : public sf::Drawable, public sf::Transformable {

    private:
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
      std::vector<std::shared_ptr<sf::Drawable>> drawables;

      std::shared_ptr<TileMap> map;

      int x{0},y{0};
    public:
      Realm();
      void update(float deltaTime, sf::RenderWindow* window);
  };
}

#endif