#ifndef REALM_HPP
#define REALM_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace sl {
  class Realm : public sf::Drawable, public sf::Transformable {

    private:
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
      std::vector<std::shared_ptr<sf::Drawable>> drawables;

    public:
      Realm();
  };
}

#endif