#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    struct HUD
    {
        sf::Text score;
        sf::Text speed;

        sf::Text wasdHint;
        sf::Text escapeHint;

        sf::Text gameOver;
    };

    struct Game;

    void InitHUD(HUD& hud, const sf::Font& font);

    void UpdateHUD(HUD& hud, const Game& game);

    void DrawHUD(const HUD& hud, sf::RenderWindow& window);

    void DrawGameOver(const HUD& hud, sf::RenderWindow& window);
}
