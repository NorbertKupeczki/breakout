#ifndef BREAKOUT_BALL_H
#define BREAKOUT_BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Ball
{
 public:
  Ball();
  ~Ball();

  sf::Sprite ball_sprite;

  bool in_play;
  float getSpeed();
  void setSpeed(float speed);
  void increaseSpeed();
  float getX();
  float getY();
  void reverseX();
  void normalise();
  void randomiseDirection();
  bool collisionCheck(sf::RenderWindow& window, sf::Sprite p1, sf::Sprite p2);
  void wallBounce();
  void adjustAngle(sf::Sprite paddle);
  void setStartLocation(float loc);
  float getStartLocation();

 private:
  sf::SoundBuffer wall_bounce_bf;
  sf::SoundBuffer paddle_bounce_bf;
  sf::Sound wall_bounce;
  sf::Sound paddle_bounce;

  sf::Texture ball_texture;
  struct Vector2
  {
    float x;
    float y;
  };

  Vector2 ball_vector;
  float ball_speed;
  float y_loc;

};

#endif // BREAKOUT_BALL_H
