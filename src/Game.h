
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  void initTextures();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:
  sf::Texture& texturePicker(int row);

  sf::RenderWindow& window;
  sf::Texture red_brick;
  sf::Texture blue_brick;
  sf::Texture green_brick;
  sf::Texture grey_brick;
  sf::Texture purple_brick;
  sf::Texture yellow_brick;

  const int GRID_SIZE = 16;
  const int OFFSET = 28;

  Paddle paddle;
  Ball ball;

  GameObject* brick_array;

  enum Scene
  {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_OVER = 2
  };

  Scene active_scene;

};

#endif // BREAKOUT_GAME_H
