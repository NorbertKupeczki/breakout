#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  brick_state = BRICK;
}

GameObject::~GameObject()
{

}

void GameObject::setTexture(sf::Texture &colour)
{
  sprite.setTexture(colour);
}

void GameObject::setBrickPos(float x_pos, float y_pos)
{
  sprite.setPosition(x_pos, y_pos);
}

void GameObject::setState(std::string state)
{
  if (state == "brick")
  {
    brick_state = BRICK;
  }
  else if (state == "diamond")
  {
    brick_state = DIAMOND;
  }
  else
  {
    brick_state = DESTROYED;
  }
}

bool GameObject::isBrick()
{
  if (brick_state == BRICK)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool GameObject::isDiamond()
{
  if (brick_state == DIAMOND)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool GameObject::isInGame()
{
  if (brick_state == BRICK || brick_state == DIAMOND)
  {
    return true;
  }
  else
  {
    return false;
  }
}

sf::Sprite GameObject::getSprite()
{
  return sprite;
}

