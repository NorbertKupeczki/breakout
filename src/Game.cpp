
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

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

  paddle.setPaddlePos(window.getSize().x / 2 - paddle.getSprite().getGlobalBounds().width / 2, window.getSize().y - 50.0);
  ball.resetBall(paddle.getSprite());

  brick_1.setTexture(green_brick);
  brick_1.setBrickPos(100.0,100.0);
  brick_2.setTexture(red_brick);
  brick_2.setBrickPos(200.0,100.0);


  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
  window.draw(paddle.getSprite());
  window.draw(ball.getSprite());
  window.draw(brick_1.getSprite());
  window.draw(brick_2.getSprite());
}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}


