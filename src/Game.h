
#ifndef BREAKOUT_GAME_H
#define BREAKOUT_GAME_H

#include <SFML/Graphics.hpp>
#include "Vector2.h"
#include "Ball.h"
#include "Paddle.h"
#include "GameObject.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  void initTextures();
  bool init();
  void update(float dt);
  void render();
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);

 private:
  sf::Texture& texturePicker(int row);
  sf::Texture& gemTexturePicker();
  void loadTexture(sf::Texture& texture,sf::Sprite& sprite, std::string path);
  void loadTexture(sf::Texture& texture, std::string path);
  void resetBricks();

  sf::RenderWindow& window;
  sf::Texture bg_texture;
  sf::Sprite bg_sprite;

  sf::Texture red_brick;
  sf::Texture blue_brick;
  sf::Texture green_brick;
  sf::Texture grey_brick;
  sf::Texture purple_brick;
  sf::Texture yellow_brick;

  sf::Texture red_gem;
  sf::Texture blue_gem;
  sf::Texture green_gem;
  sf::Texture grey_gem;
  sf::Texture purple_gem;
  sf::Texture yellow_gem;

  sf::Texture menu_bg_texture;
  sf::Sprite menu_bg_sprite;
  sf::Texture start_a_texture;
  sf::Texture start_i_texture;
  sf::Sprite start_sprite;
  sf::Texture quit_a_texture;
  sf::Texture quit_i_texture;
  sf::Sprite quit_sprite;
  sf::Texture keys_texture;
  sf::Sprite keys_sprite;
  sf::Texture game_over_w_texture;
  sf::Texture game_over_l_texture;
  sf::Sprite game_over_sprite;
  sf::Texture again_a_texture;
  sf::Texture again_i_texture;
  sf::Sprite again_sprite;

  sf::Font font;
  sf::Text lives;
  sf::Text score;

  const int GRID_SIZE = 16;
  const int OFFSET = 28;

  Paddle paddle;
  Ball ball;
  Gem* gem;

  Brick* brick_array;

  enum Scene
  {
    MAIN_MENU = 0,
    IN_GAME = 1,
    GAME_OVER = 2
  };

  Scene active_scene;
  bool start_active = true;

};

#endif // BREAKOUT_GAME_H
