
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Ball.h"
#include "Paddle.h"

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

};

#endif // BREAKOUT_GAME_H
