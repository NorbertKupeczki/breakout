
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
  delete[] brick_array;
}

void Game::initTextures()
{
  if(!red_brick.loadFromFile("Data/Images/element_red_rectangle.png"))
  {
    std::cout << "Red brick texture didn't load\n";
  }
  if(!blue_brick.loadFromFile("Data/Images/element_blue_rectangle.png"))
  {
    std::cout << "Blue brick texture didn't load\n";
  }
  if(!green_brick.loadFromFile("Data/Images/element_green_rectangle.png"))
  {
    std::cout << "Red brick texture didn't load\n";
  }
  if(!grey_brick.loadFromFile("Data/Images/element_grey_rectangle.png"))
  {
    std::cout << "Blue brick texture didn't load\n";
  }
  if(!purple_brick.loadFromFile("Data/Images/element_purple_rectangle.png"))
  {
    std::cout << "Red brick texture didn't load\n";
  }
  if(!yellow_brick.loadFromFile("Data/Images/element_yellow_rectangle.png"))
  {
    std::cout << "Blue brick texture didn't load\n";
  }
}

bool Game::init()
{
  initTextures();

  paddle.setPaddlePos(
    window.getSize().x / 2 - paddle.getSprite().getGlobalBounds().width / 2,
    window.getSize().y - 50.0
    );
  ball.resetBall(paddle.getSprite());

  brick_array = new GameObject[GRID_SIZE * (GRID_SIZE/2)];
  for (int i = 0; i < GRID_SIZE / 2; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      brick_array[j + i * GRID_SIZE].setBrickPos(
        j * red_brick.getSize().x + OFFSET,
        i * red_brick.getSize().y + OFFSET
        );
      brick_array[j + i * GRID_SIZE].setTexture(texturePicker(i));
    }
  }

  return true;
}

void Game::update(float dt)
{
  paddle.movePaddle(window, dt);
  ball.moveBall(paddle.getSprite(), dt);
  ball.collisionCheck(window,
                      paddle.getSprite(),
                      brick_array,
                      GRID_SIZE*(GRID_SIZE / 2));
}

void Game::render()
{
  window.draw(paddle.getSprite());
  window.draw(ball.getSprite());
  for (int i = 0; i < GRID_SIZE * (GRID_SIZE/2); i++)
  {
    if (brick_array[i].isInGame())
    {
      window.draw(brick_array[i].getSprite());
    }
  }
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (event.key.code == sf::Keyboard::Space)
  {
    ball.setBallOnPaddle(false);
  }

  if  (event.key.code == sf::Keyboard::Left)
  {
    paddle.setDir(-1.0);
  }
  else if (event.key.code == sf::Keyboard::Right)
  {
    paddle.setDir(1.0);
  }
}

void Game::keyReleased(sf::Event event)
{
  if  (event.key.code == sf::Keyboard::Left ||
       event.key.code == sf::Keyboard::Right)
  {
    paddle.setDir(0);
  }
}

sf::Texture & Game::texturePicker(int row)
{
  switch (row % 6)
  {
    case 0:
      return green_brick;
    case 1:
      return yellow_brick;
    case 2:
      return red_brick;
    case 3:
      return blue_brick;
    case 4:
      return grey_brick;
    case 5:
      return purple_brick;
  }
}


