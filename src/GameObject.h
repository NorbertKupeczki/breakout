
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vector2.h"

class Brick
{
 public:
  Brick();
  ~Brick();

  void setTexture(sf::Texture& colour);
  void setBrickPos(float x_pos, float y_pos);
  void setState(bool state);
  bool isInGame();
  int getValue();
  sf::Sprite getSprite();

 private:
  bool in_game;
  int value;
  sf::Sprite sprite;
};

class Gem
{
 public:
  Gem();
  ~Gem();

  void setTexture(sf::Texture& colour);
  void spawnGem(float window, sf::Texture& colour);
  bool getState();
  float getCountdown();
  void reduceCountdown(float dt);
  bool moveGem(float window, sf::Sprite paddle, float dt);
  sf::Sprite getSprite();
  int getValue();

 private:
  void resetCountdown();
  void setState(bool state);
  void setPos(float x_pos);

  sf::SoundBuffer gem_bf;
  sf::Sound gem_snd;

  const int SPAWN_TIME = 4;
  float spawn_countdown;
  bool in_game;
  float gem_speed;
  int value;
  sf::Sprite sprite;
};


#endif // BREAKOUT_GAMEOBJECT_H
