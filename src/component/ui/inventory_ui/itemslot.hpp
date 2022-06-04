#ifndef ITEMSLOT_HPP
#define ITEMSLOT_HPP

#include "../ui_element.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

namespace sl {
  namespace ui {
    class ItemSlots : public sf::Drawable, public sf::Transformable {
      private:
        std::vector<sf::RectangleShape*> itemSlots;
      public:
        ItemSlots() {
          for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 9; j++) {
              sf::RectangleShape* rect = new sf::RectangleShape{{20, 20}};
              rect->setPosition(j * 50 + 10, i * 50 + 10);
              rect->setFillColor(sf::Color::Red);
              itemSlots.push_back(rect);
            }
          }

        }

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
          states.transform *= getTransform();
          

          for (auto x : itemSlots) {
            target.draw(*x, states);
          }
        }



        ~ItemSlots() {
          for (auto x : itemSlots) {
            delete(x);
          }
          itemSlots.clear();
        }

        ItemSlots(const ItemSlots&) = delete;
        ItemSlots& operator=(const ItemSlots&) = delete;
    };
  };
};

#endif