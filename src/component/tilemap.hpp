#include <SFML/Graphics.hpp>  
#include <unordered_map>
#include <iostream>

namespace sl {

  struct Tile {
        int x, y;
        sf::Vertex* quad;
        int value;
    private:
        bool valid = false;
    public:
        bool isTileValid() const { return valid; }
        
        explicit Tile(sf::Vertex* quad, int x, int y, int value) : x(x), y(y), value(value), quad(quad), valid(true) {}
        Tile() : valid(false), x(0), y(0), quad(nullptr), value(0) {}

        Tile(const Tile& other): x(other.x), y(other.y), quad(other.quad), value(other.value)  {
        }

        void setMaterial(int material) { 
            value = material;
        };

        int getMaterial() const { return value; }
  };

  struct vec2i {
    int x, y;
    vec2i(int x, int y) : x(x), y(y) {}

    bool operator==(const vec2i& other) const {
        if (x == other.x && y == other.y) return true;
        return false;
    }
  };

    struct hash_fn
    {
        std::size_t operator() (const vec2i &node) const
        {
            std::size_t h1 = std::hash<int>()(node.x);
            std::size_t h2 = std::hash<int>()(node.y);
    
            return h1 ^ h2;
        }
    };

  class TileMap : public sf::Drawable, public sf::Transformable
  {
  public:

      bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
      {
          // load the tileset texture
          if (!m_tileset.loadFromFile(tileset))
              return false;
          this->tileSize = tileSize;
          this->tiles = tiles;
          this->width = width;

          // resize the vertex array to fit the level size
          m_vertices.setPrimitiveType(sf::Quads);
          m_vertices.resize(width * height * 4);

          // populate the vertex array, with one quad per tile
          for (unsigned int i = 0; i < width; ++i)
              for (unsigned int j = 0; j < height; ++j)
              {
                  // get the current tile number
                  int tileNumber = tiles[i + j * width];

                  // find its position in the tileset texture
                  int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                  int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                  // get a pointer to the current tile's quad
                  sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                  // define its 4 corners
                  quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                  quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                  quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                  quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                  // define its 4 texture coordinates
                  quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                  quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                  quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                  quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

                  tile_vector.insert({vec2i(i, j), Tile(quad, i, j, tileNumber)}); 
                  std::cout << "inserted at " << i << " -- " << j << std::endl;
              }

          return true;
      }

      void updateTile(Tile& tile) {
           // find its position in the tileset texture
        int tu = tile.getMaterial() % (m_tileset.getSize().x / tileSize.x);
        int tv = tile.getMaterial() / (m_tileset.getSize().x / tileSize.x);

        // get a pointer to the current tile's quad
        sf::Vertex* quad = &m_vertices[(tile.x + tile.y * width) * 4];

        // define its 4 corners
        quad[0].position = sf::Vector2f(tile.x * tileSize.x, tile.y * tileSize.y);
        quad[1].position = sf::Vector2f((tile.x + 1) * tileSize.x, tile.y * tileSize.y);
        quad[2].position = sf::Vector2f((tile.x + 1) * tileSize.x, (tile.y + 1) * tileSize.y);
        quad[3].position = sf::Vector2f(tile.x * tileSize.x, (tile.y + 1) * tileSize.y);

        // define its 4 texture coordinates
        quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
        quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
        quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
        quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
}

      Tile setMaterialOfTile(int x, int y, int material) {
          Tile tile = getTileFromIndex(x, y);
          tile.setMaterial(material);

          return tile;
      }


      Tile getTileFromIndex(int x, int y) {
        if (tile_vector.find(vec2i(x,y)) != tile_vector.end())
            return tile_vector.at(vec2i(x,y));
        else
            return emptyTile();
      }

      sf::Texture* getTexture() { return &m_tileset; }

  private:

    Tile emptyTile() {
        return Tile();
    }

      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
      {
          // apply the transform
          states.transform *= getTransform();

          // apply the tileset texture
          states.texture = &m_tileset;

          // draw the vertex array
          target.draw(m_vertices, states);
      }

      sf::VertexArray m_vertices;
      sf::Texture m_tileset;
      std::unordered_map<vec2i, Tile, hash_fn> tile_vector;

      sf::Vector2u tileSize;
      unsigned int width;
      const int* tiles;
  };
}