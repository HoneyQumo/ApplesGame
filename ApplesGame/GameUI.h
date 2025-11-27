#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    struct GameUI
    {
        sf::Text score;

        sf::Text wasdHint;
        sf::Text escapeHint;

        sf::Text gameOver;
    };

    struct Game;

    void InitUI(GameUI& gameUI, const sf::Font& font);

    void UpdateUI(GameUI& gameUI, const Game& game);

    void DrawUI(const GameUI& gameUI, sf::RenderWindow& window, const Game& game);
}
