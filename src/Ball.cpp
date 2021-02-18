#include "Ball.h"
#include <iostream>
#include <cmath>

Ball::Ball()
{
  std::cout << "Ball appears\n";
  ball_speed = 400.0f;
  score = 0;

  if(!ball_texture.loadFromFile("Data/Images/ballGrey.png"))
  {
    std::cout << "ball texture didn't load\n";
  }
  ball_sprite.setTexture(ball_texture);

  in_play = true;
  ball_on_paddle = true;

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

  if (!brick_break_bf.loadFromFile("Data/Sounds/break.ogg"))
  {
    std::cout << "Brick break sound didn't load to buffer!\n";
  }
  brick_break.setBuffer(brick_break_bf);
}

Ball::~Ball()
{
  std::cout << "Ball object removed\n";
}

bool Ball::inPlay()
{
  return in_play;
}

int Ball::getScore()
{
  return score;
}

void Ball::addScore(int value)
{
  score += value;
}

void Ball::resetScore()
{
  score = 0;
}

void Ball::reverseX()
{
  ball_vector.x = -1.0 * ball_vector.x;
}

void Ball::reverseY()
{
  ball_vector.y = -1.0 * ball_vector.y;
}

bool Ball::collisionCheck(sf::RenderWindow& window,
                          sf::Sprite paddle,
                          Brick* brick_array,
                          int array_size)
{
  int brick_index;
  float distance = 500.0;
  bool brick_hit = false;

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
        window.getSize().x - ball_sprite.getGlobalBounds().width)
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

  for (int i=0; i<array_size; i++)
  {
    if (ball_sprite.getGlobalBounds().intersects(brick_array[i].getSprite().getGlobalBounds()) &&
        brick_array[i].isInGame())
    {
      float br_x = brick_array[i].getSprite().getPosition().x +
                   brick_array[i].getSprite().getGlobalBounds().width / 2;
      float br_y = brick_array[i].getSprite().getPosition().y +
                   brick_array[i].getSprite().getGlobalBounds().height / 2;
      float ball_x = ball_sprite.getPosition().x +
                     ball_sprite.getGlobalBounds().width / 2;
      float ball_y = ball_sprite.getPosition().y +
                     ball_sprite.getGlobalBounds().height / 2;
      float new_distance = getDist(br_x,br_y,ball_x, ball_y);
      if (new_distance < distance)
      {
        distance = new_distance;
        brick_index = i;
      }
      brick_hit = true;
    }
  }

  if (brick_hit)
  {
    brickBounce(brick_array[brick_index]);
    return true;
  }
  else
  {
    return false;
  }
}

void Ball::moveBall(sf::Sprite paddle, float dt)
{
  if (ball_on_paddle)
  {
    ball_sprite.setPosition(
      paddle.getPosition().x + paddle.getGlobalBounds().width / 2 -
        ball_sprite.getGlobalBounds().width / 2,
      ball_sprite.getPosition().y);
  }
  else
  {
    ball_sprite.move(
      ball_vector.x * ball_speed * dt,
      ball_vector.y * ball_speed * dt
      );
  }
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
  ball_vector.x = new_x;
  ball_vector.y = -1.0 * sqrt(1 - pow(new_x, 2));
  ball_vector.normalise();
}

void Ball::brickBounce(Brick& brick)
{
  bool bounce_x = false;
  bool bounce_y = false;
  // To handle the bounce from the ball that has been hit
  float ball_rad = ball_sprite.getGlobalBounds().width /2;
  float ball_x = ball_sprite.getPosition().x + ball_rad;
  float ball_y = ball_sprite.getPosition().y + ball_rad;
  int br_left = brick.getSprite().getPosition().x;
  int br_right = brick.getSprite().getPosition().x +
                 brick.getSprite().getGlobalBounds().width;
  int br_top = brick.getSprite().getPosition().y;
  int br_bottom = brick.getSprite().getPosition().y +
                  brick.getSprite().getGlobalBounds().height;

  if (ball_vector.x < 0.0 && ball_vector.y < 0.0)
  {
    if ((br_left <= ball_x && ball_x <= br_right) ||
         getDist(ball_x, ball_y, br_left, br_bottom) <= ball_rad)
    {
      bounce_y = true;
    }
    else if ((br_top <= ball_y && ball_y <= br_bottom) ||
              getDist(ball_x, ball_y, br_right, br_top) <= ball_rad)
    {
      bounce_x = true;
    }
    else
    {
      if (ball_x - br_right <= ball_y - br_bottom)
      {
        bounce_y = true;
      }
      else
      {
        bounce_x = true;
      }
    }
  }
  else if (ball_vector.x > 0.0 && ball_vector.y < 0.0)
  {
    if ((br_left <= ball_x && ball_x <= br_right) ||
        getDist(ball_x, ball_y, br_right, br_bottom) <= ball_rad)
    {
      bounce_y = true;
    }
    else if ((br_top <= ball_y && ball_y <= br_bottom) ||
             getDist(ball_x, ball_y, br_left, br_top) <= ball_rad)
    {
      bounce_x = true;
    }
    else
    {
      if (br_left - ball_x <= ball_y - br_bottom)
      {
        bounce_y = true;
      }
      else
      {
        bounce_x = true;
      }
    }
  }
  else if (ball_vector.x > 0.0 && ball_vector.y > 0.0)
  {
    if ((br_left <= ball_x && ball_x <= br_right) ||
        getDist(ball_x, ball_y, br_right, br_top) <= ball_rad)
    {
      bounce_y = true;
    }
    else if ((br_top <= ball_y && ball_y <= br_bottom) ||
             getDist(ball_x, ball_y, br_left, br_bottom) <= ball_rad)
    {
      bounce_x = true;
    }
    else
    {
      if (br_left - ball_x <= br_top - ball_y)
      {
        bounce_y = true;
      }
      else
      {
        bounce_x = true;
      }
    }
  }
  else if (ball_vector.x < 0.0 && ball_vector.y > 0.0)
  {
    if ((br_left <= ball_x && ball_x <= br_right) ||
        getDist(ball_x, ball_y, br_left, br_top) <= ball_rad)
    {
      bounce_y = true;
    }
    else if ((br_top <= ball_y && ball_y <= br_bottom) ||
             getDist(ball_x, ball_y, br_right, br_bottom) <= ball_rad)
    {
      bounce_x = true;
    }
    else
    {
      if (ball_x - br_right <= br_top - ball_y)
      {
        bounce_y = true;
      }
      else
      {
        bounce_x = true;
      }
    }
  }
  else if (ball_vector.x == 0.0)
  {
    if (br_left < ball_x && ball_x < br_right)
    {
      bounce_y = true;
    }
    else if (getDist(ball_x, ball_y, br_left, br_bottom) <= ball_rad)
    {
      ball_vector.x = -0.3;
      bounce_y = true;
      ball_vector.normalise();
    }
    else if (getDist(ball_x, ball_y, br_right, br_bottom) <= ball_rad)
    {
      ball_vector.x = 0.3;
      bounce_y = true;
      ball_vector.normalise();
    }
  }

  if (bounce_x)
  {
    reverseX();
    if (ball_vector.x < 0.0 && ball_vector.x > -0.3)
    {
      ball_vector.x = -0.3;
      ball_vector.normalise();
    }
    else if (ball_vector.x > 0.0 && ball_vector.x < 0.3)
    {
      ball_vector.x = 0.3;
      ball_vector.normalise();
    }
    brick.setState(false);
  }
  else if (bounce_y)
  {
    reverseY();
    brick.setState(false);
  }
  addScore(brick.getValue());
  brick_break.play();
  number_of_bricks--;
}

void Ball::resetBall(sf::Sprite paddle)
{
  ball_sprite.setPosition(
    paddle.getPosition().x + paddle.getGlobalBounds().width / 2 -
    ball_sprite.getGlobalBounds().width / 2,
    paddle.getPosition().y - ball_sprite.getGlobalBounds().height);
  ball_on_paddle = true;
  in_play = true;
}

bool Ball::isBallOnPaddle()
{
  return ball_on_paddle;
}

void Ball::setBallOnPaddle(bool state)
{
  ball_on_paddle = state;
}

sf::Sprite Ball::getSprite()
{
  return ball_sprite;
}

float Ball::getDist(float a1, float a2, float b1, float b2)
{
  return sqrt(pow(a1 - b1,2) + pow(a2 - b2,2));
}

void Ball::increaseBrickCount()
{
  number_of_bricks++;
}

int Ball::getBrickCount()
{
  return number_of_bricks;
}

void Ball::setBrickCount(int count)
{
  number_of_bricks = count;
}