#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "scene.hpp"

namespace sl {
  class MenuScene : public sl::Scene {
      
    public:

      MenuScene() : Scene("menu_scene") {
        
      }
  };
};

#endif