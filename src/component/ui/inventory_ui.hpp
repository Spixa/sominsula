#ifndef INVENTORY_UI_HPP
#define INVENTORY_UI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ui_element.hpp"

// depend
#include "inventory_ui/itemslot.hpp"

namespace sl {
  class Player;

  namespace ui {
    class InventoryUI : public ui::UiElement {
      private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        Player* playerPtr;
        sf::RectangleShape outerShape;
        ui::ItemSlots slots;
        bool isVisible{false};
      public:
        explicit InventoryUI(Player* player);
        void setVisible(bool visibility) { isVisible = visibility; }
        void toggleVisibility() {
          if (isVisible) {
            setVisible(false);
          } else {
            setVisible(true);
          }
        }

        InventoryUI(const InventoryUI&) = delete;
        InventoryUI& operator=(const InventoryUI&) = delete;

    };
  }
};

#endif