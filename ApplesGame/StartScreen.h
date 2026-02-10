#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace ApplesGame
{
    struct StartScreen
    {
        sf::Text title;
        sf::Text exitHint;
        sf::Text startHint;

        sf::Text modeSettingsTitle;
        sf::Text isInfiniteMode;
        sf::Text isAcceleratedMode;
    };

    struct Game;

    void InitStartScreen(StartScreen& screen, const sf::Font& font);

    void UpdateStartScreen(StartScreen& screen, const Game& game);

    void DrawStartScreen(const StartScreen& screen, sf::RenderWindow& window);

    void StartScreenKeyboardHandler(const sf::Event& event, Game& game);
}
