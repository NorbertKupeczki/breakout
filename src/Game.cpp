
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

}

bool Game::init()
{
  initTextures();

  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{

}

void Game::keyPressed(sf::Event event)
{

}

void Game::keyReleased(sf::Event event)
{

}


