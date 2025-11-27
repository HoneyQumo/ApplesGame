#pragma once
#include <thread>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"
#include "Sounds.h"
#include "HUD.h"

namespace ApplesGame
{
    struct Game
    {
        GameSoundBuffer soundBuffer;
        GameSound sound;

        sf::Font font;
        HUD hud;

        Player player;
        Apple apples[TOTAL_APPLES];
        Rock rocks[TOTAL_ROCKS];
        int numEatenApples = 0;
        bool isGameOver = false;

        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture rockTexture;
    };

    void RestartGame(Game& game);

    void InitGame(Game& game);

    void UpdateGame(Game& game, const float& time);

    void DrawGame(sf::RenderWindow& window, Game& game);

    void KeyboardHandler(PlayerDirection& playerDirection);
}
