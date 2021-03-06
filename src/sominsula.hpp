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
      sf::Clock deltaTimeClock{};
      float deltaTime{};

      static Sominsula* m_instance;
    protected:
      void init();
      void loop();
      void render();
      void update();
      float getDeltaTime();

    protected: // updates
      void update_events();
      Sominsula();

    public:
      int exec();
      sf::RenderWindow* getWindow() { return window.get(); }

      static Sominsula* getInstance();
  };

  Sominsula& getGame();

}

#endif