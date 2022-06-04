#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP	

#include "scene.hpp"
#include <SFML/Graphics.hpp>

#include "../realm/realm.hpp"

namespace sl {
  namespace ui { class InventoryUI; }
  class GameScene : public sl::Scene {
      std::shared_ptr<Realm> realm;
      std::shared_ptr<ui::InventoryUI> inv;
    public:
      GameScene();

      void update(float deltaTime, sf::RenderWindow* window) override;
      
  };
};

#endif