
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
  active_scene = MAIN_MENU;
}

Game::~Game()
{
  delete[] brick_array;
}

void Game::initTextures()
{
  loadTexture(bg_texture, bg_sprite, "Data/Images/bground.png");

  loadTexture(red_brick, "Data/Images/element_red_rectangle.png");
  loadTexture(blue_brick, "Data/Images/element_blue_rectangle.png");
  loadTexture(green_brick, "Data/Images/element_green_rectangle.png");
  loadTexture(grey_brick, "Data/Images/element_grey_rectangle.png");
  loadTexture(purple_brick, "Data/Images/element_purple_rectangle.png");
  loadTexture(yellow_brick, "Data/Images/element_yellow_rectangle.png");

  loadTexture(red_gem, "Data/Images/element_red_polygon_glossy.png");
  loadTexture(blue_gem, "Data/Images/element_blue_polygon_glossy.png");
  loadTexture(green_gem, "Data/Images/element_green_polygon_glossy.png");
  loadTexture(grey_gem, "Data/Images/element_grey_polygon_glossy.png");
  loadTexture(purple_gem, "Data/Images/element_purple_polygon_glossy.png");
  loadTexture(yellow_gem, "Data/Images/element_yellow_polygon_glossy.png");

  loadTexture(menu_bg_texture, menu_bg_sprite, "Data/Images/main_menu.png");
  loadTexture(start_a_texture, start_sprite, "Data/Images/start_active.png");
  loadTexture(start_i_texture, "Data/Images/start_inactive.png");
  loadTexture(quit_a_texture, "Data/Images/quit_active.png");
  loadTexture(quit_i_texture, quit_sprite, "Data/Images/quit_inactive.png");
  loadTexture(keys_texture, keys_sprite, "Data/Images/keys.png");
  loadTexture(game_over_w_texture, "Data/Images/gameover_won.png");
  loadTexture(game_over_l_texture, game_over_sprite, "Data/Images/gameover_lost.png");
  loadTexture(again_a_texture, again_sprite, "Data/Images/again_active.png");
  loadTexture(again_i_texture, "Data/Images/again_inactive.png");
}

bool Game::init()
{
  initTextures();
  menu_bg_sprite.setPosition(
    window.getSize().x / 2 - menu_bg_sprite.getGlobalBounds().width / 2,
    window.getSize().y / 3 - menu_bg_sprite.getGlobalBounds().height / 2);
  keys_sprite.setPosition(
    window.getSize().x / 2 - keys_sprite.getGlobalBounds().width / 2,
    window.getSize().y * 3 / 4 - keys_sprite.getGlobalBounds().height / 2);
  start_sprite.setPosition(
    window.getSize().x / 2 - start_sprite.getGlobalBounds().width / 2,
    window.getSize().y * 0.28 - start_sprite.getGlobalBounds().height / 2);
  quit_sprite.setPosition(
    window.getSize().x / 2 - quit_sprite.getGlobalBounds().width / 2,
    window.getSize().y * 0.4 - quit_sprite.getGlobalBounds().height / 2);

  game_over_sprite.setPosition(
    window.getSize().x / 2 - game_over_sprite.getGlobalBounds().width / 2,
    window.getSize().y / 3 - game_over_sprite.getGlobalBounds().height / 2);
  again_sprite.setPosition(
    window.getSize().x / 2 - again_sprite.getGlobalBounds().width / 2,
    window.getSize().y * 0.28 - again_sprite.getGlobalBounds().height / 2);

  paddle.setPaddlePos(
    window.getSize().x / 2 - paddle.getSprite().getGlobalBounds().width / 2,
    window.getSize().y - 50.0);
  ball.resetBall(paddle.getSprite());

  gem = new Gem;
  gem->setTexture(gemTexturePicker());

  brick_array = new Brick[GRID_SIZE * (GRID_SIZE / 2)];
  for (int i = 0; i < GRID_SIZE / 2; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      brick_array[j + i * GRID_SIZE].setBrickPos(
        j * red_brick.getSize().x + OFFSET, i * red_brick.getSize().y + OFFSET);
      ball.increaseBrickCount();
      brick_array[j + i * GRID_SIZE].setTexture(texturePicker(i));
    }
  }

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Font did not load \n";
  }

  lives.setString("Lives: " + std::to_string(paddle.getLives()));
  lives.setFont(font);
  lives.setCharacterSize(25);
  lives.setFillColor(sf::Color(200, 200, 200, 255));
  lives.setPosition(10.0, window.getSize().y - 30);

  score.setString("Score: " + std::to_string(ball.getScore()));
  score.setFont(font);
  score.setCharacterSize(25);
  score.setFillColor(sf::Color(200, 200, 200, 255));
  score.setPosition(window.getSize().x - 200, window.getSize().y - 30);

  return true;
}

void Game::update(float dt)
{
  if (active_scene == IN_GAME)
  {
    lives.setString("Lives: " + std::to_string(paddle.getLives()));
    score.setString("Score: " + std::to_string(ball.getScore()));
    paddle.movePaddle(window, dt);
    ball.moveBall(paddle.getSprite(), dt);
    ball.collisionCheck(
      window, paddle.getSprite(), brick_array, GRID_SIZE * (GRID_SIZE / 2));

    if (gem->getState())
    {
      if (gem->moveGem(window.getSize().y, paddle.getSprite(), dt))
      {
        ball.addScore(gem->getValue());
      }
    }
    else if (!gem->getState())
    {
      if (gem->getCountdown() <= 0.0)
      {
        gem->spawnGem(window.getSize().x, gemTexturePicker());
      }
      else
      {
        gem->reduceCountdown(dt);
      }
    }

    if (!ball.inPlay())
    {
      ball.resetBall(paddle.getSprite());
      paddle.loseLife();
    }

    if (paddle.getLives() <= 0)
    {
      active_scene = GAME_OVER;
    }
    else if(ball.getBrickCount() <= 0)
    {
      game_over_sprite.setTexture(game_over_w_texture);
      active_scene = GAME_OVER;
    }
  }
}

void Game::render()
{
  window.draw(bg_sprite);
  window.draw(paddle.getSprite());
  window.draw(ball.getSprite());
  for (int i = 0; i < GRID_SIZE * (GRID_SIZE/2); i++)
  {
    if (brick_array[i].isInGame())
    {
      window.draw(brick_array[i].getSprite());
    }
  }
  if (active_scene == MAIN_MENU)
  {
    window.draw(menu_bg_sprite);
    window.draw(start_sprite);
    window.draw(quit_sprite);
    window.draw(keys_sprite);
  }
  else if (active_scene == GAME_OVER)
  {
    window.draw(game_over_sprite);
    window.draw(again_sprite);
    window.draw(quit_sprite);
  }
  if (gem->getState())
  {
    window.draw(gem->getSprite());
  }
  window.draw(lives);
  window.draw(score);
}

void Game::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }

  if (active_scene == MAIN_MENU)
  {
    if (event.key.code == sf::Keyboard::Up ||
        event.key.code == sf::Keyboard::Down)
    {
      start_active = !start_active;
      if (start_active)
      {
        start_sprite.setTexture(start_a_texture);
        quit_sprite.setTexture(quit_i_texture);
      }
      else
      {
        start_sprite.setTexture(start_i_texture);
        quit_sprite.setTexture(quit_a_texture);
      }
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (start_active)
      {
        active_scene = IN_GAME;
      }
      else
      {
        window.close();
      }
    }
  }

  if (active_scene == IN_GAME)
  {
    if (event.key.code == sf::Keyboard::Space && ball.isBallOnPaddle())
    {
      ball.setBallOnPaddle(false);
    }

    if (event.key.code == sf::Keyboard::Left)
    {
      paddle.setDir(-1.0);
    }
    else if (event.key.code == sf::Keyboard::Right)
    {
      paddle.setDir(1.0);
    }
  }

  else if (active_scene == GAME_OVER)
  {
    if (event.key.code == sf::Keyboard::Up ||
        event.key.code == sf::Keyboard::Down)
    {
      start_active = !start_active;
      if (start_active)
      {
        again_sprite.setTexture(again_a_texture);
        quit_sprite.setTexture(quit_i_texture);
      }
      else
      {
        again_sprite.setTexture(again_i_texture);
        quit_sprite.setTexture(quit_a_texture);
      }
    }
    if (event.key.code == sf::Keyboard::Enter)
    {
      if (start_active)
      {
        paddle.resetPaddle(window);
        paddle.resetLives();
        ball.resetBall(paddle.getSprite());
        ball.resetScore();
        resetBricks();
        ball.setBrickCount(GRID_SIZE * GRID_SIZE / 2);
        active_scene = IN_GAME;
      }
      else
      {
        window.close();
      }
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (active_scene == IN_GAME)
  {
    if (event.key.code == sf::Keyboard::Left ||
        event.key.code == sf::Keyboard::Right)
    {
      paddle.setDir(0);
    }
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

sf::Texture & Game::gemTexturePicker()
{
  int rnd = rand() % 6;
  switch (rnd)
  {
    case 0:
      return green_gem;
    case 1:
      return yellow_gem;
    case 2:
      return red_gem;
    case 3:
      return blue_gem;
    case 4:
      return grey_gem;
    case 5:
      return purple_gem;
  }
}

void Game::loadTexture(sf::Texture& texture,sf::Sprite& sprite, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
  sprite.setTexture(texture);
}

void Game::loadTexture(sf::Texture& texture, std::string path)
{
  if(!texture.loadFromFile(path))
  {
    std::cout << path <<" texture didn't load\n";
  }
}

void Game::resetBricks()
{
  for (int i = 0; i < GRID_SIZE * (GRID_SIZE/2); i++)
  {
    brick_array[i].setState(true);
  }
}


