#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    enum class PauseOptionKey
    {
        Continue = 0,
        ExitToMenu
    };

    struct HUD
    {
        sf::Text score;
        sf::Text speed;

        /* Todo: Переделать подсказки клавиш на список */
        sf::Text wasdHint;
        sf::Text escapeHint;

        sf::Text gameOver;

        /* Todo: Переделать подсказки клавиш на список */
        sf::Text pauseTitle;
        sf::Text pauseToggleOptionHint;
        sf::Text pauseSelectHint;
        std::map<PauseOptionKey, MenuOption> pauseOptions = {
            {PauseOptionKey::Continue, {"Continue", {}}},
            {PauseOptionKey::ExitToMenu, {"Exit to menu", {}}},
        };
        PauseOptionKey pauseSelectedOptionKey;
    };

    struct Game;

    void InitHUD(HUD& hud, const sf::Font& font);
    void UpdateHUD(HUD& hud, const Game& game);
    void DrawHUD(sf::RenderWindow& window, const HUD& hud);

    void DrawGameOver(sf::RenderWindow& window, const HUD& hud);

    void InitPause(HUD& hud, const sf::Font& font);
    void DrawPause(sf::RenderWindow& window, const HUD& hud);
    void PauseKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);
    void PauseOptionSelectHandler(sf::RenderWindow& window, Game& game);
    void SetPauseOptionKey(HUD& hud, const PauseOptionKey& newKey);
}
