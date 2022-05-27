#include "realm.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>


#include "../component/entity/player.hpp"

namespace sl {
  void Realm::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    target.draw(*dispMap.get());

    for (auto X : entities) {
      target.draw(*X, states);
    }

  }

  Realm::Realm() : map(std::make_shared<TileMap>()), dispMap(std::make_shared<DisplayableTileMap>(map->getTexture())) {

    std::vector<int> levelVector;

    int i,j;
    for (i = 0; i < 80; i++) {
      for (j = 0; j < 80; j++) {
        levelVector.push_back(0);
      }
    }

    map->setScale(2, 2);
    dispMap->setScale(2, 2);

    mapSizeX = i;
    mapSizeY = j;

    if (!map->load("tileset.png", sf::Vector2u(32, 32), &levelVector[0], mapSizeX, mapSizeY))
        throw std::runtime_error("can't load tileset");

    entities.push_back(std::make_shared<Player>());
  }

  void Realm::update(float deltaTime, sf::RenderWindow* window) {
    for (auto X : entities) {
      X->update_entity(deltaTime, window, map.get());
    }

    float viewCenterX = window->getView().getCenter().x;
    float viewCenterY = window->getView().getCenter().y;

    float viewSizeWidth = window->getView().getSize().x;
    float viewSizeHeight = window->getView().getSize().y;


    int topLeftY = std::floor((viewCenterY - (viewSizeHeight / 2)) / 32 / map->getScale().y);
    int downLeftY = std::floor((viewCenterY + (viewSizeHeight / 2)) / 32 / map->getScale().y);

    int topRightX = std::floor(((viewCenterX + (viewSizeWidth / 2)) / 32 / map->getScale().x));
    int topLeftX = std::floor((viewCenterX - (viewSizeWidth / 2)) / 32 / map->getScale().x);

    // int downLeftX = std::floor(((viewCenterX - (viewSizeWidth / 2)) / 32 / map->getScale().x));
    // int downRightX = std::floor((viewCenterX + (viewSizeWidth / 2)) / 32 / map->getScale().x);
    // int downRightY = std::floor((viewCenterY + (viewSizeHeight / 2)) / 32 / map->getScale().y);
    // int topRightY = std::floor((viewCenterY - (viewSizeHeight / 2)) / 32 / map->getScale().y);
    // std::cout << "----------------------------------------------------------------" << std::endl;
    // std::cout << topLeftX << " -- " << topLeftY << " || " << topRightX << " -- " << topRightY << "\n" << downLeftX << " -- " << downLeftY << " || " << downRightX << " -- " << downRightY << std::endl;
    // std::cout << "----------------------------------------------------------------" << std::endl;

    std::vector<Tile> tiles;


    for (int j = topLeftY; j < downLeftY; j = j + 1 ) {
      for (int i  = topLeftX; i < topRightX; i++) {
        tiles.push_back(Tile(map->getTileFromIndex(i, j)));
      }
    }

    dispMap->update(tiles);

  }
};