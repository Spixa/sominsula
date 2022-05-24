#ifndef SOMINSULA_HPP
#define SOMINSULA_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <memory>
#include <vector>
#include "scene/scene_manager.hpp"


namespace sl {
  class Sominsula : public sf::NonCopyable {
      std::unique_ptr<sf::RenderWindow> window;
      constexpr static uint32_t default_width{800}, default_height{400};
      sf::String default_title{"Sominsula"};
      
      SceneManager manager;
      

      static Sominsula* m_instance;
    protected:
      void init();
      void loop();
      void render();
      void update();

    protected: // updates
      void update_events();
      Sominsula();

    public:
      int exec();

      static Sominsula* getInstance();
  };

  Sominsula& getGame();

}

#endif