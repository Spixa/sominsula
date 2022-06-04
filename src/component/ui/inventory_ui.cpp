#include "inventory_ui.hpp"
#include "../entity/player.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include "../../sominsula.hpp"
#include "inventory_ui/itemslot.hpp"

namespace sl {
  namespace ui {

    InventoryUI::InventoryUI(Player* player) : UiElement(), outerShape{}, slots() {
      playerPtr = player;
      outerShape.setSize({460, 210});
      outerShape.setOrigin({230, 105});


      pushUIElement(&outerShape);
      pushUIElement(&slots, -220, -100);
    }

    void InventoryUI::draw(sf::RenderTarget& target, sf::RenderStates states) const {
      if (isVisible) {
        states.transform *= getTransform(); // Apply transform
        target.draw(outerShape, states);
        target.draw(slots, states);
      }
    }

  };
};