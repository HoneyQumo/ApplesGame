#pragma once
#include <thread>
#include "Constants.h"
#include "Player.h"
#include "Apple.h"

namespace ApplesGame
{
    struct Game
    {
        Player player;
        Apple apple[TOTAL_APPLES];
        int numEatenApples = 0;
    };

    void InitGame(Game& game);

    void UpdateGame(Game& game, const float& time);

    void DrawGame(sf::RenderWindow& window, Game& game);

    void KeyboardHandler(PlayerDirection& playerDirection);
}
