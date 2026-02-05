#include "Game.h"

namespace ApplesGame
{
    void InitHUD(HUD& hud, const sf::Font& font)
    {
        const sf::Color whiteSemiTransparent(255, 255, 255, 100);

        hud.score.setString("Score: ");
        hud.score.setFont(font);
        hud.score.setCharacterSize(24);
        hud.score.setFillColor(sf::Color::Yellow);
        hud.score.setPosition(SCREEN_PADDING, SCREEN_PADDING);

        hud.speed.setString("Speed: ");
        hud.speed.setFont(font);
        hud.speed.setCharacterSize(24);
        hud.speed.setFillColor(sf::Color::White);
        hud.speed.setPosition(SCREEN_PADDING, SCREEN_PADDING + 30.f);

        hud.wasdHint.setString("Controls [WASD] / Arrows");
        hud.wasdHint.setFont(font);
        hud.wasdHint.setCharacterSize(16);
        hud.wasdHint.setFillColor(whiteSemiTransparent);
        hud.wasdHint.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - SCREEN_PADDING);
        hud.wasdHint.setOrigin(GetTextOrigin(hud.wasdHint, {0.5f, 1.f}));

        hud.escapeHint.setString("Menu [ESC]");
        hud.escapeHint.setFont(font);
        hud.escapeHint.setCharacterSize(16);
        hud.escapeHint.setFillColor(whiteSemiTransparent);
        hud.escapeHint.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        hud.escapeHint.setOrigin(GetTextOrigin(hud.escapeHint, {1.f, 0.f}));

        hud.gameOver.setString("GAME OVER");
        hud.gameOver.setFont(font);
        hud.gameOver.setStyle(sf::Text::Bold);
        hud.gameOver.setCharacterSize(48);
        hud.gameOver.setFillColor(sf::Color::Red);
        hud.gameOver.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        hud.gameOver.setOrigin(GetTextOrigin(hud.gameOver, {0.5f, 0.5f}));
    }

    void UpdateHUD(HUD& hud, const Game& game)
    {
        hud.score.setString("Score: " + std::to_string(game.numEatenApples));
        hud.speed.setString("Speed: " + std::to_string(static_cast<int>(game.player.speed)));
    }

    void DrawHUD(const HUD& hud, sf::RenderWindow& window, const Game& game)
    {
        window.draw(hud.score);
        window.draw(hud.speed);
        window.draw(hud.wasdHint);
        window.draw(hud.escapeHint);

        if (game.isGameOver)
        {
            window.draw(hud.gameOver);
        }
    }
}
