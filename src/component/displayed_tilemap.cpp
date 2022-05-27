#include "displayed_tilemap.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include "tilemap.hpp"

namespace sl {
  DisplayableTileMap::DisplayableTileMap(sf::Texture* texture) : m_texture(texture) {
    m_vertices.setPrimitiveType(sf::Quads);
  }

  void DisplayableTileMap::update(const std::vector<Tile>& tiles) {
    m_vertices.clear();
    for (auto x : tiles) {
      if (x.quad == nullptr) continue;
      m_vertices.append(x.quad[0]);
      m_vertices.append(x.quad[1]);
      m_vertices.append(x.quad[2]);
      m_vertices.append(x.quad[3]);
    }
  } 

  void DisplayableTileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // apply the transform
    states.transform *= getTransform();

    // apply the tileset texture
    states.texture = m_texture;

    // draw the vertex array
    target.draw(m_vertices, states);
  }
};