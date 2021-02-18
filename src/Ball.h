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

  bool inPlay();

  // Score accessors and mutators
  int getScore();
  void addScore(int value);
  void resetScore();

  // Vector accessors and mutators
  void reverseX();
  void reverseY();
  void moveBall(sf::Sprite, float dt);
  void adjustAngle(sf::Sprite paddle);
  void brickBounce(Brick& brick);
  bool collisionCheck(sf::RenderWindow& window,
                      sf::Sprite paddle,
                      Brick* brick_array,
                      int array_size);

  // Auxiliary functions
  void resetBall(sf::Sprite paddle);
  bool isBallOnPaddle();
  void setBallOnPaddle(bool state);
  void increaseBrickCount();
  void setBrickCount(int count);
  int getBrickCount();

  sf::Sprite getSprite();

 private:
  float getDist(float a1, float a2, float b1, float b2);
  sf::Sprite ball_sprite;
  sf::SoundBuffer wall_bounce_bf;
  sf::SoundBuffer paddle_bounce_bf;
  sf::SoundBuffer brick_break_bf;
  sf::Sound wall_bounce;
  sf::Sound paddle_bounce;
  sf::Sound brick_break;

  sf::Texture ball_texture;
  Vector2 ball_vector  = {0.0, - 1.0};;
  float ball_speed;
  bool ball_on_paddle;
  bool in_play;
  int score;
  int number_of_bricks = 0;

};

#endif // BREAKOUT_BALL_H
