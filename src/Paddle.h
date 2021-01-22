#ifndef BREAKOUT_PADDLES_H
#define BREAKOUT_PADDLES_H

#include <SFML/Graphics.hpp>

class Paddle
{
 public:
  Paddle();
  ~Paddle();

  sf::Sprite paddle_sprite;

  int getScore();
  void addScore();
  void resetScore();

  float getDir();
  void setDir(float dir);
  float getSpeed();
  void setSpeed(float speed);
  void setColor(int player);
  void resetPaddle(sf::RenderWindow& window);

 private:
  sf::Texture paddle_texture_red;
  sf::Texture paddle_texture_blue;
  int score;
  float paddle_speed;
  float y_dir;

};

#endif // BREAKOUT_PADDLES_H
