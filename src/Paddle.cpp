#include "Paddle.h"
#include <iostream>

Paddle::Paddle()
{
  std::cout << "Paddle created\n";
  if(!paddle_texture_blue.loadFromFile("Data/Images/paddleBlue.png"))
  {
    std::cout << "Red paddle texture didn't load\n";
  }
  paddle_sprite.setTexture(paddle_texture_blue);

  paddle_speed = 300.0f;
  score = 0;
  lives = 3;
}

Paddle::~Paddle()
{
  std::cout << "Paddle removed\n";
}

int Paddle::getScore()
{
  return score;
}

void Paddle::addScore(int value)
{
  score += value;
}

void Paddle::resetScore()
{
  score = 0;
}

int Paddle::getLives()
{
  return lives;
}

void Paddle::loseLife()
{
  lives--;
}

void Paddle::addLife()
{
  lives++;
}

void Paddle::resetLives()
{
  lives = 3;
}

float Paddle::getDir()
{
  return vector.x;
}

void Paddle::setDir(float dir)
{
  if (dir > 0.0)
  {
    vector.x = 1.0;
  }
  else if (dir < 0.0)
  {
    vector.x = -1.0;
  }
  else if (dir == 0.0)
  {
    vector.x = 0.0;
  }
}

float Paddle::getSpeed()
{
  return paddle_speed;
}

sf::Sprite Paddle::getSprite()
{
  return paddle_sprite;
}

void Paddle::setPaddlePos(float x_pos, float y_pos)
{
  paddle_sprite.setPosition(x_pos,y_pos);
}

void Paddle::setSpeed(float speed)
{
  paddle_speed = speed;
}

void Paddle::movePaddle(sf::RenderWindow& window, float dt)
{
  float paddle_pos_l = paddle_sprite.getPosition().x;
  float paddle_pos_r = paddle_sprite.getPosition().x
                       + paddle_sprite.getGlobalBounds().width;

  if (paddle_pos_l + paddle_speed * vector.x * dt < 0.0)
  {
    paddle_sprite.setPosition(0.0, paddle_sprite.getPosition().y);
  }
  else if (paddle_pos_r + paddle_speed * vector.x * dt > window.getSize().x)
  {
    paddle_sprite.setPosition(
      window.getSize().x - paddle_sprite.getGlobalBounds().width,
      paddle_sprite.getPosition().y
      );
  }
  else
  {
    paddle_sprite.move(paddle_speed * vector.x * dt, 0.0);
  }
}

void Paddle::resetPaddle(sf::RenderWindow& window)
{
  paddle_sprite.setPosition(
    window.getSize().x / 2 - paddle_sprite.getLocalBounds().width / 2,
    paddle_sprite.getPosition().y);
  setDir(0.0);
}

