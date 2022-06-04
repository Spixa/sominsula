#ifndef UI_ELEMENT_HPP
#define UI_ELEMENT_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "../../sominsula.hpp"

namespace sl {
  namespace ui {
    class UiElement : public sf::Drawable, public sf::Transformable {
      private:
        struct Element {
          sf::Transformable* pTransformable;
          float xOffset;
          float yOffset;
        };

        std::vector<Element> renderElements;
      protected:
        void pushUIElement(sf::Transformable* t, const float xOffset = 0, const float yOffset = 0) {
          
          Element e{};
          e.pTransformable = t;
          e.xOffset = xOffset;
          e.yOffset = yOffset;

          renderElements.push_back(e);
        
        }
      public:
        UiElement() {}
        void update(float deltaTime, sf::RenderWindow* window) {
          for (auto x : renderElements) {
            x.pTransformable->setPosition(getGame().getWindow()->getView().getCenter().x + x.xOffset, getGame().getWindow()->getView().getCenter().y + x.yOffset);
          }
        }
    };
  };
};

#endif