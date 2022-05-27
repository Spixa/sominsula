#ifndef DISP_TILEMAP_HPP
#define DISP_TILEMAP_HPP

#include <SFML/Graphics.hpp>

namespace sl {
  class Tile;
  class DisplayableTileMap : public sf::Drawable, public sf::Transformable {
    public: 
      explicit DisplayableTileMap(sf::Texture* texture);

      void update(const std::vector<Tile>& tiles);
    private:
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

      sf::Texture* m_texture;
      sf::VertexArray m_vertices;
   };
};

#endif