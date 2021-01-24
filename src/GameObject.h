
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  bool in_game;
  void setTexture(sf::Texture &colour);
  void setBrickPos(float x_pos, float y_pos);
  sf::Sprite getSprite();

 private:
  sf::Sprite sprite;


};



#endif // BREAKOUT_GAMEOBJECT_H
