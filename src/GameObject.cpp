#include "GameObject.h"
#include <iostream>

// ------------------------- BRICK -------------------------
Brick::Brick()
{
  in_game = true;
  value = 10;

}

Brick::~Brick()
{

}

void Brick::setTexture(sf::Texture& colour)
{
  sprite.setTexture(colour);
}

void Brick::setBrickPos(float x_pos, float y_pos)
{
  sprite.setPosition(x_pos, y_pos);
}

void Brick::setState(bool state)
{
  in_game = state;
}

bool Brick::isInGame()
{
  return in_game;
}

int Brick::getValue()
{
  return value;
}

sf::Sprite Brick::getSprite()
{
  return sprite;
}

// ------------------------- GEM -------------------------

Gem::Gem()
{
  gem_speed = 125.0;
  in_game = false;
  value = 25;
  spawn_countdown = SPAWN_TIME * 2;

  if (!gem_bf.loadFromFile("Data/Sounds/gem.ogg"))
  {
    std::cout << "Gem sound didn't load to buffer!\n";
  }
  gem_snd.setBuffer(gem_bf);
}

Gem::~Gem()
{

}

void Gem::setState(bool state)
{
  in_game = state;
}

bool Gem::getState()
{
  return in_game;
}

void Gem::setTexture(sf::Texture& colour)
{
  sprite.setTexture(colour);
}

void Gem::spawnGem(float window, sf::Texture& colour)
{
  setState(true);
  int max_y = window - sprite.getGlobalBounds().width;
  int rnd = rand() % max_y;
  setPos(rnd);
  setTexture(colour);
  resetCountdown();

}

void Gem::setPos(float x_pos)
{
  sprite.setPosition(x_pos, -sprite.getGlobalBounds().height);
}

float Gem::getCountdown()
{
  return spawn_countdown;
}

void Gem::reduceCountdown(float dt)
{
  spawn_countdown -= dt;
}

void Gem::resetCountdown()
{
  spawn_countdown = SPAWN_TIME;
}

bool Gem::moveGem(float window, sf::Sprite paddle, float dt)
{
  sprite.move(0.0, gem_speed * dt);
  if (sprite.getPosition().y > window)
  {
    setState(false);
  }
  else if (sprite.getGlobalBounds().intersects(paddle.getGlobalBounds()))
  {
    setState(false);
    gem_snd.play();
    return true;
  }
  return false;
}

sf::Sprite Gem::getSprite()
{
  return sprite;
}

int Gem::getValue()
{
  return value;
}