#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"

class Ball
{
 public:
  Ball();
  ~Ball();

  bool in_play;

  // Vector and speed accessors and mutators
  float getSpeed();
  void setSpeed(float speed);
  void increaseSpeed();
  float getX();
  float getY();
  void reverseX();
  void reverseY();
  void randomiseDirection();
  void adjustAngle(sf::Sprite paddle);

  bool collisionCheck(sf::RenderWindow& window, sf::Sprite paddle);

  void resetBall(sf::Sprite paddle);

  sf::Sprite getSprite();

 private:
  sf::Sprite ball_sprite;
  sf::SoundBuffer wall_bounce_bf;
  sf::SoundBuffer paddle_bounce_bf;
  sf::Sound wall_bounce;
  sf::Sound paddle_bounce;

  sf::Texture ball_texture;
  Vector2 ball_vector = {0.0f,0.0f};
  float ball_speed;
  float x_loc;

};

#endif // BREAKOUT_BALL_H
