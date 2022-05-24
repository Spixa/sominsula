#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include "game_scene.hpp"
#include "scene.hpp"
#include "menu_scene.hpp"

namespace sl {
  enum class Scenes : unsigned long {
    MainMenuScene = 0,
    GameScene = 1,
  };

  class SceneManager {
      std::vector<Scene*> scenes;
      Scene* runningScene;
      Scenes runningSceneType;
  
    public:
      SceneManager() {
        // load all scenes
        scenes.push_back(new MenuScene());
        scenes.push_back(new GameScene());

        runningScene = scenes[0];
        runningSceneType = Scenes::MainMenuScene;
      }

      void render(sf::RenderWindow* window) {
        if (runningScene) {
          runningScene->render(window);
        }
      }

      Scenes getCurrentScene() {
        return runningSceneType;
      }

      void loadScene(Scenes const& s) {
        if (s == runningSceneType) return;
        
        switch (s) {
          case Scenes::MainMenuScene:
            runningScene = scenes[static_cast<unsigned long>(Scenes::MainMenuScene)];
            runningSceneType = Scenes::MainMenuScene;
          break;
          case Scenes::GameScene:
            runningScene = scenes[static_cast<unsigned long>(Scenes::GameScene)];
            runningSceneType = Scenes::GameScene;
          break;
          default:
            
          break;
        }
      }
  };
};

#endif