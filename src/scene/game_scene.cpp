#include "game_scene.hpp"
#include "../sominsula.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../component/ui/inventory_ui.hpp"

namespace sl {
  GameScene::GameScene() : Scene("game_scene"), realm(std::make_shared<Realm>()) {
    pushDrawable(realm);

    inv = std::make_shared<ui::InventoryUI>(realm->getMainPlayer());
    pushDrawable(inv);

    registerEvent([&](sf::Event event) {
        if (event.type == sf::Event::KeyPressed) {
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            inv->toggleVisibility();
          }
        }
    });
  }

  void GameScene::update(float deltaTime, sf::RenderWindow* window) {
    realm->update(deltaTime, window);
    inv->update(deltaTime, window);
        
  }


};