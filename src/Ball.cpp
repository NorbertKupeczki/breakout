#include "Ball.h"
#include <iostream>
#include <cmath>

Ball::Ball()
{
  std::cout << "Ball appears\n";
  ball_speed = 0.0f;

  if(!ball_texture.loadFromFile("Data/Images/ballGrey.png"))
  {
    std::cout << "ball texture didn't load\n";
  }
  ball_sprite.setTexture(ball_texture);

  in_play = true;

  if (!wall_bounce_bf.loadFromFile("Data/Sounds/wall_bounce.wav"))
  {
    std::cout << "Wall bounce sound didn't load to buffer!\n";
  }
  wall_bounce.setBuffer(wall_bounce_bf);

  if (!paddle_bounce_bf.loadFromFile("Data/Sounds/paddle_bounce.ogg"))
  {
    std::cout << "Paddle bounce sound didn't load to buffer!\n";
  }
  paddle_bounce.setBuffer(paddle_bounce_bf);
}

Ball::~Ball()
{
  std::cout << "Ball object removed\n";
}

float Ball::getSpeed()
{
  return ball_speed;
}

void Ball::setSpeed(float speed)
{
  ball_speed = speed;
}

void Ball::increaseSpeed()
{
  ball_speed += 20.0;
}

void Ball::randomiseDirection()
{
  if (rand() % 2 == 1)
  {
    reverseX();
  }
}

float Ball::getX()
{
  return ball_vector.x;
}

float Ball::getY()
{
  return ball_vector.y;
}

void Ball::reverseX()
{
  ball_vector.x = -1.0 * ball_vector.x;
}

void Ball::reverseY()
{
  ball_vector.y = -1.0 * ball_vector.y;
}

bool Ball::collisionCheck(sf::RenderWindow& window, sf::Sprite paddle)
{
  if (ball_vector.y < 0.0 && ball_sprite.getPosition().y <= 0)
  {
    reverseY();
    wall_bounce.play();
    return true;
  }

  if (
    ball_vector.x < 0.0 && ball_sprite.getPosition().x <= 0.0f ||
    ball_vector.x > 0.0 &&
      ball_sprite.getPosition().x >=
        window.getSize().x - ball_sprite.getGlobalBounds().width / 2)
  {
    reverseX();
    wall_bounce.play();
    return true;
  }

  if (ball_sprite.getGlobalBounds().intersects(paddle.getGlobalBounds()))
  {
    adjustAngle(paddle);
    // increaseSpeed();
    paddle_bounce.play();
    return true;
  }

  if (
    ball_vector.y > 0.0 &&
    ball_sprite.getPosition().y + ball_sprite.getGlobalBounds().height >=
      window.getSize().y)
  {
    in_play = false;
  }

  return false;
}

void Ball::adjustAngle(sf::Sprite paddle)
{
  float ball_mid =
    ball_sprite.getPosition().x + ball_sprite.getLocalBounds().width / 2;
  float paddle_mid =
    paddle.getPosition().x + paddle.getLocalBounds().width / 2;
  float dist  = paddle_mid - ball_mid;
  float new_x = dist /
                (paddle.getLocalBounds().width / 2 +
                 ball_sprite.getLocalBounds().width / 2) *
                (1 / sqrt(2)) * -1.0;
  ball_vector.y = new_x;
  if (ball_vector.x < 0.0)
  {
    ball_vector.y = sqrt(1 - pow(new_x, 2));
  }
  else
  {
    ball_vector.y = -1.0 * sqrt(1 - pow(new_x, 2));
  }
  ball_vector.normalise();
}

void Ball::resetBall(sf::Sprite paddle)
{
  ball_sprite.setPosition(
    paddle.getPosition().x + paddle.getGlobalBounds().width / 2 -
    ball_sprite.getGlobalBounds().width / 2,
    paddle.getPosition().y - ball_sprite.getGlobalBounds().height);
}

sf::Sprite Ball::getSprite()
{
  return ball_sprite;
}