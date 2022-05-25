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
    manager.update(0.f, window.get());
    
  }

  void Sominsula::update_events() {
    using sf::Event;

    Event event;
    while (window->pollEvent(event)) {
      switch (event.type) {
        case Event::Closed:
          // TODO: add function to handle saves before termination
          window->close(); // close upon using the X button or Alt+F4
        break;
        default:
          
        break;
      }
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