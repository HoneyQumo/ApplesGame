#include "GameUI.h"
#include "Game.h"


namespace ApplesGame
{
    void InitUI(GameUI& gameUI, const sf::Font& font)
    {
        const sf::Color whiteSemiTransparent(255, 255, 255, 100);

        gameUI.score.setString("Score: ");
        gameUI.score.setFont(font);
        gameUI.score.setCharacterSize(24);
        gameUI.score.setFillColor(sf::Color::Yellow);
        gameUI.score.setPosition(SCREEN_PADDING, SCREEN_PADDING);

        gameUI.wasdHint.setString("Controls - W A S D / Arrows");
        gameUI.wasdHint.setFont(font);
        gameUI.wasdHint.setCharacterSize(16);
        gameUI.wasdHint.setFillColor(whiteSemiTransparent);
        gameUI.wasdHint.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - SCREEN_PADDING);
        gameUI.wasdHint.setOrigin(GetTextOrigin(gameUI.wasdHint, {0.5f, 1.f}));

        gameUI.escapeHint.setString("Exit - ESC");
        gameUI.escapeHint.setFont(font);
        gameUI.escapeHint.setCharacterSize(16);
        gameUI.escapeHint.setFillColor(whiteSemiTransparent);
        gameUI.escapeHint.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        gameUI.escapeHint.setOrigin(GetTextOrigin(gameUI.escapeHint, {1.f, 0.f}));

        gameUI.gameOver.setString("GAME\nOVER");
        gameUI.gameOver.setFont(font);
        gameUI.gameOver.setStyle(sf::Text::Bold);
        gameUI.gameOver.setCharacterSize(48);
        gameUI.gameOver.setFillColor(sf::Color::Red);
        gameUI.gameOver.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
        gameUI.gameOver.setOrigin(GetTextOrigin(gameUI.gameOver, {0.5f, 0.5f}));
    }

    void UpdateUI(GameUI& gameUI, const Game& game)
    {
        gameUI.score.setString("Score: " + std::to_string(game.numEatenApples));
    }

    void DrawUI(const GameUI& gameUI, sf::RenderWindow& window, const Game& game)
    {
        window.draw(gameUI.score);
        window.draw(gameUI.wasdHint);
        window.draw(gameUI.escapeHint);

        if (game.isGameOver)
        {
            window.draw(gameUI.gameOver);
        }
    }
}
