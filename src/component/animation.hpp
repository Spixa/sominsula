#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <SFML/Graphics.hpp>

namespace sl {
	class Entity;
	class Animation final {
    // Functions:
    public:
      Animation(Entity* entity, sf::String const& texture,sf::Vector2u imageCount,float switchTime);
      void update(int row,float deltaTime);
      ~Animation();

    // Variables:
    public:
      sf::IntRect animRect; // Animation Integer rectangle 
      bool isFacingRight = true;
      void flipTexture();
    private:
      sf::Vector2u imageCount; // total image {x,y}
      sf::Vector2u currentImage; // image we are currently on {known_x,y}

      float totalTime;  // period of time since last switch was applied.
      float switchTime; // period of time takes to switch to another buffer

      sf::Texture* texture;
      Entity* entity;
      sf::Image* flippedTextureImage;
      sf::Texture* flippedTexture;
	};
}
#endif