#include "Game.h"
#include <cassert>

namespace ApplesGame
{
    void InitGame(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));

        InitPlayer(game.player, game.playerTexture);

        game.numEatenApples = 0;

        for (Apple& apple : game.apples)
        {
            InitApple(apple, game.appleTexture);
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
            if (IsCircleCollide(
                    game.player.position, PLAYER_SIZE / 2.f,
                    game.apples[i].position, APPLE_SIZE / 2.f)
            )
            {
                /* Count eated apples */
                ++game.numEatenApples;

                /* Init new apple */
                InitApple(game.apples[i], game.appleTexture);

                game.player.speed += PLAYER_ACCELERATION;
            }
        }
    }

    void DrawGame(sf::RenderWindow& window, Game& game)
    {
        DrawPlayer(game.player, window);

        for (Apple& apple : game.apples)
        {
            DrawApple(apple, window);
        }
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
}
