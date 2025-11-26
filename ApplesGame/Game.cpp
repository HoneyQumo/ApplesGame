#include <cassert>
#include "Game.h"

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        game.isGameOver = false;
        game.numEatenApples = 0;

        InitSounds(game.sound, game.soundBuffer);
        InitPlayer(game.player, game.playerTexture);

        for (Apple& apple : game.apples)
        {
            InitApple(apple, game.appleTexture);
        }

        for (Rock& rock : game.rocks)
        {
            InitRock(rock, game.rockTexture);
        }
    }

    void InitGame(Game& game)
    {
        /* Textures */
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\Player.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\Apple.png"));
        assert(game.rockTexture.loadFromFile(RESOURCES_PATH + "\\Rock.png"));

        /* Sounds */
        assert(game.soundBuffer.playerDeath.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        assert(game.soundBuffer.appleEat.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));

        RestartGame(game);
    }

    void UpdateGame(Game& game, const float& time)
    {
        if (game.isGameOver)
        {
            game.sound.playerDeath.play();

            /* Pause GAME LOOP */
            std::this_thread::sleep_for(std::chrono::seconds(1));

            RestartGame(game);
        }
        else
        {
            /* Set player direction */
            KeyboardHandler(game.player.direction);

            UpdatePlayerMovement(game.player, time);

            if (HasPlayerCollisionWithWindowBorder(game.player.position))
            {
                game.isGameOver = true;
            }

            /* Player to Apple collision */
            for (Apple& apple : game.apples)
            {
                if (IsCircleCollide(
                        game.player.position, PLAYER_SIZE / 2.f,
                        apple.position, APPLE_SIZE / 2.f)
                )
                {
                    game.sound.appleEat.play();

                    /* Count eated apples */
                    ++game.numEatenApples;

                    /* Init new apple */
                    InitApple(apple, game.appleTexture);

                    game.player.speed += PLAYER_ACCELERATION;
                }
            }

            /* Player to Rock collision */
            for (Rock& rock : game.rocks)
            {
                if (IsRectangleCollide(
                        game.player.position, {PLAYER_SIZE, PLAYER_SIZE},
                        rock.position, {ROCK_SIZE, ROCK_SIZE})
                )
                {
                    game.isGameOver = true;
                }
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


        for (Rock& rock : game.rocks)
        {
            DrawRock(rock, window);
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
