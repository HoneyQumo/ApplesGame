#include <cassert>
#include "Game.h"

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        UpdateLeaderboard(game.leaderboard);

        game.totalApples = TOTAL_APPLES;
        game.apples = std::make_unique<Apple[]>(game.totalApples);
        game.playerScore = 0;

        game.isShowStartScreen = true;
        game.isGameOver = false;

        InitSounds(game.sound, game.soundBuffer);
        InitStartScreen(game.leaderboard, game.startScreen, game.font);
        InitHUD(game.hud, game.font);
        InitPlayer(game.player, game.playerTexture);

        for (unsigned int i = 0; i < game.totalApples; ++i)
        {
            Apple& apple = game.apples[i];
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

        /* Fonts */
        assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

        game.leaderboard = GenerateRandomLeaderboard(5);
        RestartGame(game);
    }

    void UpdateGame(Game& game, const float& time)
    {
        if (game.isShowStartScreen)
        {
            UpdateStartScreen(game.startScreen, game);
            return;
        }


        if (game.isGameOver)
        {
            game.sound.playerDeath.play();

            /* Pause GAME LOOP */
            std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_BEFORE_RESTART_IN_SECONDS));

            UpdatePlayerPosition(game.playerScore, game.player.name, game.leaderboard);
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
            for (unsigned int i = 0; i < game.totalApples; ++i)
            {
                if (IsCircleCollide(
                        game.player.position, PLAYER_SIZE / 2.f,
                        game.apples[i].position, APPLE_SIZE / 2.f)
                )
                {
                    game.sound.appleEat.play();

                    /* Count eated apples */
                    ++game.playerScore;

                    if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite))
                    {
                        /* Init new apple */
                        InitApple(game.apples[i], game.appleTexture);
                    }
                    else
                    {
                        /* Delete collision apple */
                        auto newApples = std::make_unique<Apple[]>(game.totalApples - 1);

                        std::copy(game.apples.get(), game.apples.get() + i, newApples.get());
                        std::copy(game.apples.get() + i + 1,
                                  game.apples.get() + game.totalApples,
                                  newApples.get() + i);

                        game.apples = std::move(newApples);
                        --game.totalApples;
                    }


                    if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated))
                    {
                        game.player.speed += PLAYER_ACCELERATION;
                    }
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

        UpdateHUD(game.hud, game);
    }

    void DrawGame(sf::RenderWindow& window, Game& game)
    {
        if (game.isShowStartScreen)
        {
            DrawStartScreen(game.startScreen, window);
            return;
        }

        DrawPlayer(game.player, window);

        for (unsigned int i = 0; i < game.totalApples; ++i)
        {
            DrawApple(game.apples[i], window);
        }


        for (Rock& rock : game.rocks)
        {
            DrawRock(rock, window);
        }

        DrawHUD(game.hud, window, game);
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

    bool IsEnableGameMode(const uint8_t& mode, const GameModeSettingsBitMask& mask)
    {
        return mode & static_cast<uint8_t>(mask);
    }

    void EnableGameMode(uint8_t& mode, const GameModeSettingsBitMask& mask)
    {
        mode |= static_cast<uint8_t>(mask);
    }

    void DisableGameMode(uint8_t& mode, const GameModeSettingsBitMask& mask)
    {
        mode &= ~static_cast<uint8_t>(mask);
    }

    std::vector<Leaderboard> GenerateRandomLeaderboard(const unsigned int count)
    {
        std::vector<Leaderboard> tmpArray;

        for (unsigned i = 0; i < count; ++i)
        {
            const std::string tmpPlayerName = "Player " + std::to_string(i + 1);
            const unsigned int tmpRandomScore = GetIntegerInRange(0, 100);

            tmpArray.push_back({tmpPlayerName, tmpRandomScore});
        }

        return tmpArray;
    }
}
