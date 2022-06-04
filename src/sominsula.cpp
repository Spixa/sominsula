#include "sominsula.hpp"

#include <memory>
#include <iostream>

#include "scene/menu_scene.hpp"

namespace sl {
  Sominsula* Sominsula::m_instance = nullptr;

  Sominsula::Sominsula() : manager() {
    {
      std::cout << "We directly jump into the Game Scene for now." << std::endl;
      manager.loadScene(Scenes::GameScene);
    }
  }

  ////////////////////////////////////////////////////////////////

  void Sominsula::init() {
    window = std::make_unique<sf::RenderWindow>( sf::VideoMode(default_width, default_height), default_title, sf::Style::Close | sf::Style::Resize);
  }

  void Sominsula::loop() {
    while (window->isOpen()) {
      render();
      update();
      deltaTime = getDeltaTime();
    }
  }

  void Sominsula::render() {
    window->clear();

    manager.render(window.get());

    window->display();
  }

  void Sominsula::update() {
    update_events();

    // TODO: IMPLEMENT DELTA TIME
    manager.update(deltaTime, window.get());
    
  }

  float Sominsula::getDeltaTime() {
    sf::Time dt = deltaTimeClock.restart();
    return dt.asSeconds();
  }

  void Sominsula::update_events() {
    using sf::Event;

    Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window->close();
      }

      manager.update_event(event);
    }
  }

  ////////////////////////////////////////////////////////////////

  int Sominsula::exec() {
    init();
    loop();
    return 0;
  }

  ////////////////////////////////////////////////////////////////

  Sominsula* Sominsula::getInstance() {
    if (m_instance == nullptr) {
      m_instance = new Sominsula();
    }
    return m_instance;
  }

  Sominsula& getGame()
   { return *Sominsula::getInstance(); }

} // namespace sl