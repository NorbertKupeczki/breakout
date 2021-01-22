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

  // Initialise, normalise and randomise starting vectors
  ball_vector.y = ((rand() % 8) / 10.0);
  ball_vector.x = sqrt(1-pow(ball_vector.y,2));
  normalise();
  randomiseDirection();

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
  std::cout << "New speed: " << ball_speed << "\n";
}

void Ball::normalise()
{
  float magnitude = sqrt(pow(ball_vector.x,2) + pow(ball_vector.y,2));
  ball_vector.x = ball_vector.x/magnitude;
  ball_vector.y = ball_vector.y/magnitude;
  std::cout << "X=" << ball_vector.x << " Y=" << ball_vector.y << "\n";
}

void Ball::randomiseDirection()
{
  if (rand() % 2 == 1)
  {
    ball_vector.x = -1.0 * ball_vector.x;
  }
  if (rand() % 2 == 1)
  {
    ball_vector.y = -1.0 * ball_vector.y;
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

bool Ball::collisionCheck(sf::RenderWindow& window, sf::Sprite p1, sf::Sprite p2)
{
  if ((ball_vector.y < 0.0 && ball_sprite.getPosition().y <= 0) ||
      (ball_vector.y > 0.0 && ball_sprite.getPosition().y +
       ball_sprite.getLocalBounds().height >= window.getSize().y))
  {
    wallBounce();
    wall_bounce.play();
    return true;
  }

  if (ball_sprite.getGlobalBounds().intersects(p1.getGlobalBounds()) &&
      ball_vector.x < 0.0)
  {
    adjustAngle(p1);
    increaseSpeed();
    paddle_bounce.play();
    return true;
  }

  if (ball_sprite.getGlobalBounds().intersects(p2.getGlobalBounds()) &&
      ball_vector.x > 0.0)
  {
    adjustAngle(p2);
    increaseSpeed();
    paddle_bounce.play();
    return true;
  }

  return false;
}

void Ball::wallBounce()
{
  ball_vector.y = -1.0 * ball_vector.y;
}

void Ball::adjustAngle(sf::Sprite paddle)
{
  float ball_mid = ball_sprite.getPosition().y + ball_sprite.getLocalBounds().height / 2;
  float paddle_mid = paddle.getPosition().y + paddle.getLocalBounds().height / 2;
  float dist = paddle_mid - ball_mid;
  float new_y = dist / (paddle.getLocalBounds().height / 2 + ball_sprite.getLocalBounds().height / 2)
                * (1 / sqrt(2)) * -1.0;
  ball_vector.y = new_y;
  if (ball_vector.x < 0.0)
  {
    ball_vector.x = sqrt(1-pow(new_y,2));
  }
  else
  {
    ball_vector.x = -1.0 * sqrt(1-pow(new_y,2));
  }
  normalise();
}

void Ball::setStartLocation(float loc)
{
  y_loc = loc;
}

float Ball::getStartLocation()
{
  return y_loc;
}