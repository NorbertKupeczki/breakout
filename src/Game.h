
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
  sf::RenderWindow& window;
  sf::Texture red_brick;
  sf::Texture blue_brick;
  sf::Texture green_brick;
  sf::Texture grey_brick;
  sf::Texture purple_brick;
  sf::Texture yellow_brick;

  Paddle paddle;
  Ball ball;

  GameObject brick_1;
  GameObject brick_2;

};

#endif // BREAKOUT_GAME_H
