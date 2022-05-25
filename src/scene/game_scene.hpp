#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP	

#include "scene.hpp"
#include <SFML/Graphics.hpp>

#include "../realm/realm.hpp"

namespace sl {
  class GameScene : public sl::Scene {
      std::shared_ptr<Realm> realm;
    public:
      GameScene() : Scene("game_scene"), realm(std::make_shared<Realm>()) {
          pushDrawable(realm);
      }

      void update(float deltaTime, sf::RenderWindow* window) override {
        realm->update(deltaTime, window);
      }
  };
};

#endif