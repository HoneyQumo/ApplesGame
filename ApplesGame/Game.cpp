#include "Game.h"

void InitGame(Game& game)
{
    InitPlayer(game.player);

    game.numEatenApples = 0;

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        InitApple(game.apple[i]);
    }
}

void UpdateGame(Game& game, const float& time)
{
    /* Set player direction */
    KeyboardHandler(game.player.direction);

    UpdatePlayerMovement(game.player, time);

    if (HasPlayerCollisionWithWindowBorder(game.player.position))
    {
        /* Pause GAME LOOP */
        std::this_thread::sleep_for(std::chrono::seconds(1));

        /* Reset game */
        InitGame(game);
    }

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        if (isCircleCollide(
                game.player.position, PLAYER_SIZE / 2.f,
                game.apple[i].position, APPLE_SIZE / 2.f)
        )
        {
            /* Count eated apples */
            ++game.numEatenApples;

            /* Init new apple */
            InitApple(game.apple[i]);

            game.player.speed += ACCELERATION;
        }
    }
}

void DrawGame(sf::RenderWindow& window, Game& game)
{
    game.player.texture.setPosition(game.player.position.x, game.player.position.y);
    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        window.draw(game.apple[i].texture);
    }
    window.draw(game.player.texture);
}

void KeyboardHandler(PlayerDirection& playerDirection)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerDirection = PlayerDirection::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerDirection = PlayerDirection::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerDirection = PlayerDirection::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerDirection = PlayerDirection::Down;
    }
}
