#ifndef REALM_HPP
#define REALM_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../component/entity/player.hpp"
#include "../component/displayed_tilemap.hpp"

namespace sl {
  class Realm : public sf::Drawable, public sf::Transformable{

    private:
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
      std::vector<std::shared_ptr<Entity>> entities;

      std::shared_ptr<TileMap> map;
      std::shared_ptr<DisplayableTileMap> dispMap;
      std::shared_ptr<Player> mainPlayer;
      unsigned int mapSizeX{}, mapSizeY{};
    public:
      Realm();
      void update(float deltaTime, sf::RenderWindow* window);

      void teleportEntity(Entity* entity, int x, int y);
      Player* getMainPlayer() { return mainPlayer.get(); }
  };
}

#endif