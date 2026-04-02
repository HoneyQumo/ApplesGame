#pragma once
#include <thread>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Sounds.h"
#include "HUD.h"
#include "MainMenu.h"
#include "Leaderboard.h"

namespace ApplesGame
{
    enum class GameModeSettingsBitMask: uint8_t
    {
        IsInfinite = 1 << 0,
        IsAccelerated = 1 << 1,

        Default = IsInfinite | IsAccelerated
    };

    enum class GameState
    {
        MainMenu = 0,
        Leaderboard,
        Settings,
        Playing,
        GameOver,
    };

    struct Game
    {
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;

        sf::Font font;

        GameSoundBuffer soundBuffer;
        GameSound sound;

        uint8_t mode = static_cast<uint8_t>(GameModeSettingsBitMask::Default); /* difficult settings */

        HUD hud;
        MainMenu mainMenuScreen;

        std::vector<GameState> gameStateStack;
        Player player;
        std::vector<Apple> apples;
        Rock rocks[TOTAL_ROCKS];

        LeaderboardMap leaderboard;
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

    void ResetGameState(Game& game);
    void PushGameState(Game& game, GameState state);
    void PopGameState(Game& game);
    GameState GetCurrentGameState(const Game& game);
}
