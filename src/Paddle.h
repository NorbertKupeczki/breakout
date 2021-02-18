#ifndef BREAKOUT_PADDLES_H
#define BREAKOUT_PADDLES_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class Paddle
{
 public:
  Paddle();
  ~Paddle();

  // Lives accessors and mutators
  int getLives();
  void loseLife();
  void resetLives();

  // Vector and speed accessors and mutators
  void setDir(float dir);
  void movePaddle(sf::RenderWindow& window, float dt);

  // Sprite accessor and mutator
  sf:: Sprite getSprite();
  void setPaddlePos(float x_pos, float y_pos);

  // Reset paddle to the middle position
  void resetPaddle(sf::RenderWindow& window);

 private:
  sf::Sprite paddle_sprite;
  sf::Texture paddle_texture_blue;
  int lives;
  float paddle_speed;
  Vector2 vector = {0.0f,0.0f};
};

#endif // BREAKOUT_PADDLES_H
