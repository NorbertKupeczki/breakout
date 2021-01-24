#include "GameObject.h"
#include <iostream>

GameObject::GameObject()
{
  std::cout << "object initialised";
}

GameObject::~GameObject()
{
  std::cout << "object removed";
}

void GameObject::setTexture(sf::Texture &colour)
{
  sprite.setTexture(colour);
}

void GameObject::setBrickPos(float x_pos, float y_pos)
{
  sprite.setPosition(x_pos, y_pos);
}

sf::Sprite GameObject::getSprite()
{
  return sprite;
}

