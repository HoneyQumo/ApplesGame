#pragma once
#include <thread>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Sounds.h"
#include "HUD.h"
#include "StartScreen.h"
#include "Leaderboard.h"

namespace ApplesGame
{
    enum class GameModeSettingsBitMask
    {
        IsInfinite = 1 << 0,
        IsAccelerated = 1 << 1,
    };

    struct Game
    {
        unsigned int playerScore = 0;

        bool isShowStartScreen = true;
        bool isGameOver = false;

        uint8_t mode = 0; /* difficult settings */

        GameSoundBuffer soundBuffer;
        GameSound sound;

        sf::Font font;
        HUD hud;
        StartScreen startScreen;

        Player player;
        std::vector<Apple> apples;
        Rock rocks[TOTAL_ROCKS];

        LeaderboardMap leaderboard;

        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;
    };

    void RestartGame(Game& game);

    void InitGame(Game& game);

    void UpdateGame(Game& game, const float& time);

    void DrawGame(sf::RenderWindow& window, Game& game);

    void KeyboardHandler(PlayerDirection& playerDirection);

    bool IsEnableGameMode(const uint8_t& mode, const GameModeSettingsBitMask& mask);

    void EnableGameMode(uint8_t& mode, const GameModeSettingsBitMask& mask);

    void DisableGameMode(uint8_t& mode, const GameModeSettingsBitMask& mask);

    LeaderboardMap GenerateRandomLeaderboard(unsigned int count = 10);
}
