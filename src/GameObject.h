
#ifndef BREAKOUT_GAMEOBJECT_H
#define BREAKOUT_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"

class GameObject
{
 public:
  GameObject();
  ~GameObject();

  void setTexture(sf::Texture &colour);
  void setBrickPos(float x_pos, float y_pos);
  void setState(std::string state);
  bool isBrick();
  bool isDiamond();
  bool isInGame();
  sf::Sprite getSprite();

 private:
  enum States
  {
    BRICK,
    DIAMOND,
    DESTROYED
  };
  States brick_state;
  sf::Sprite sprite;



};



#endif // BREAKOUT_GAMEOBJECT_H
