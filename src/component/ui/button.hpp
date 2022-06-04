#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <functional>

namespace sl {
  class Button : public sf::Drawable, public sf::Transformable{
    protected:
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
      std::function<void()> onClickEventFunction;
      sf::Vector2f size{};
      sf::Vector2f position{};

      // shapes
      sf::RectangleShape buttonRect;
      sf::Text buttonText;
      sf::Font buttonTextFont;

      // colors
      sf::Color defaultColor{};
      sf::Color hoverColor{};
      sf::Color clickColor{};
    public:
      Button();
      void update();

      void setOnClickEvent(const std::function<void()>& f);
  };
}

#endif // BUTTON_HPP