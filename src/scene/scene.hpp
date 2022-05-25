#ifndef SCENE_HPP
#define SCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <vector>
#include <memory>

namespace sl {
  class Scene : public sf::NonCopyable {
      std::vector<std::shared_ptr<sf::Drawable>> drawables;  
      sf::String name;

    public:
      explicit Scene(sf::String const& name) : name(name) {

      }

      void pushDrawable(std::shared_ptr<sf::Drawable> drawable) {
        drawables.push_back(drawable);
      }

      void render(sf::RenderWindow* window) {
        for (auto x : drawables) {
          window->draw(*x.get());
        }
      }

      virtual void update(float deltaTime, sf::RenderWindow* window) = 0;
  };
};

#endif