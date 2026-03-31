#include <cassert>
#include "Game.h"

namespace ApplesGame
{
    void RestartGame(Game& game)
    {
        game.apples.clear();
        game.playerScore = 0;

        ResetGameState(game);

        InitSounds(game.sound, game.soundBuffer);
        InitStartScreen(game.leaderboard, game.startScreen, game.font);
        InitHUD(game.hud, game.font);
        InitPlayer(game.player, game.playerTexture);

        game.apples.resize(GetIntegerInRange(1, 100));
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

        /* Fonts */
        assert(game.font.loadFromFile(RESOURCES_PATH + "\\Fonts\\Roboto-Regular.ttf"));

        game.leaderboard = GenerateRandomLeaderboard(5);
        RestartGame(game);
    }

    void UpdateGame(Game& game, const float& time)
    {
        GameState gameState = GetCurrentGameState(game);
        switch (gameState)
        {
        case GameState::Menu:
            UpdateStartScreen(game.startScreen, game);
            break;
        case GameState::GameOver:
            game.sound.playerDeath.play();
            /* Pause GAME LOOP */
            std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_BEFORE_RESTART_IN_SECONDS));
            UpdatePlayerPosition(game.playerScore, game.player.name, game.leaderboard);
            RestartGame(game);
            break;
        case GameState::Playing:
            /* Set player direction */
            KeyboardHandler(game.player.direction);

            UpdatePlayerMovement(game.player, time);

            if (HasPlayerCollisionWithWindowBorder(game.player.position))
            {
                PushGameState(game, GameState::GameOver);
            }

            /* Player to Apple collision */
            for (unsigned int i = 0; i < game.apples.size(); ++i)
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
                        game.apples.erase(game.apples.begin() + i);
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
                    PushGameState(game, GameState::GameOver);
                }
            }

        default:
            break;
        }

        UpdateHUD(game.hud, game);
    }

    void DrawGame(sf::RenderWindow& window, Game& game)
    {
        GameState gameState = GetCurrentGameState(game);
        switch (gameState)
        {
        case GameState::Menu:
            DrawStartScreen(game.startScreen, window);
            break;
        case GameState::Playing:
            DrawPlayer(game.player, window);

            for (Apple& apple : game.apples)
            {
                DrawApple(apple, window);
            }

            for (Rock& rock : game.rocks)
            {
                DrawRock(rock, window);
            }

            DrawHUD(game.hud, window);
            break;
        case GameState::GameOver:
            DrawGameOver(game.hud, window);
            break;
        default:
            break;
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

    LeaderboardMap GenerateRandomLeaderboard(const unsigned int count)
    {
        LeaderboardMap tmpArray;

        for (unsigned i = 0; i < count; ++i)
        {
            const std::string tmpPlayerName = "Player " + std::to_string(i + 1);
            const unsigned int tmpRandomScore = GetIntegerInRange(0, 100);

            tmpArray.insert({tmpPlayerName, tmpRandomScore});
        }

        return tmpArray;
    }

    void ResetGameState(Game& game)
    {
        game.gameStateStack.clear();
        PushGameState(game, GameState::Menu);
    }

    void PushGameState(Game& game, GameState state)
    {
        game.gameStateStack.push_back(state);
    }

    void PopGameState(Game& game)
    {
        if (!game.gameStateStack.empty())
        {
            game.gameStateStack.pop_back();
        }
    }

    GameState GetCurrentGameState(const Game& game)
    {
        if (!game.gameStateStack.empty())
        {
            return game.gameStateStack.back();
        }
        return GameState::Menu;
    }
}
