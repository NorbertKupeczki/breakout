#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include "GameObject.h"
#include "Vector2.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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
  void moveBall(sf::Sprite, float dt);
  void adjustAngle(sf::Sprite paddle);
  void brickBounce(GameObject& brick);

  bool collisionCheck(sf::RenderWindow& window,
                      sf::Sprite paddle,
                      GameObject* brick_array,
                      int array_size);

  void resetBall(sf::Sprite paddle);
  bool isBallOnPaddle();
  void setBallOnPaddle(bool state);

  sf::Sprite getSprite();

 private:
  float getDist(float a1, float a2, float b1, float b2);
  sf::Sprite ball_sprite;
  sf::SoundBuffer wall_bounce_bf;
  sf::SoundBuffer paddle_bounce_bf;
  sf::Sound wall_bounce;
  sf::Sound paddle_bounce;

  sf::Texture ball_texture;
  Vector2 ball_vector  = {0.0, - 1.0};;
  float ball_speed;
  float x_loc;
  bool ball_on_paddle;

};

#endif // BREAKOUT_BALL_H
