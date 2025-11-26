#pragma once
#include <thread>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"
#include "Rock.h"

namespace ApplesGame
{
    struct Game
    {
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
