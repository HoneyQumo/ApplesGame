#include "Game.h"

namespace ApplesGame
{
    void InitHUD(HUD& hud, const sf::Font& font)
    {
        const sf::Color whiteSemiTransparent(255, 255, 255, 100);

        /* Todo: Вынести в Shared.h функцию создания текста */
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

        hud.escapeHint.setString("Pause [ESC/P]");
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
        hud.score.setString("Score: " + std::to_string(game.player.score));
        hud.speed.setString("Speed: " + std::to_string(static_cast<int>(game.player.speed)));
    }

    void DrawHUD(sf::RenderWindow& window, const HUD& hud)
    {
        window.draw(hud.score);
        window.draw(hud.speed);
        window.draw(hud.wasdHint);
        window.draw(hud.escapeHint);
    }

    void DrawGameOver(sf::RenderWindow& window, const HUD& hud)
    {
        window.draw(hud.gameOver);
    }

    void InitPause(HUD& hud, const sf::Font& font)
    {
        hud.pauseSelectedOptionKey = PauseOptionKey::Continue;

        hud.pauseTitle.setString("Pause");
        hud.pauseTitle.setFont(font);
        hud.pauseTitle.setCharacterSize(36);
        hud.pauseTitle.setFillColor(sf::Color::White);
        hud.pauseTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        hud.pauseTitle.setOrigin(GetTextOrigin(hud.pauseTitle, {0.5f, 1.f}));

        hud.pauseToggleOptionHint.setString("Toggle [Arrow Up/Down]");
        hud.pauseToggleOptionHint.setFont(font);
        hud.pauseToggleOptionHint.setCharacterSize(16);
        hud.pauseToggleOptionHint.setFillColor(sf::Color::White);
        hud.pauseToggleOptionHint.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        hud.pauseToggleOptionHint.setOrigin(GetTextOrigin(hud.pauseToggleOptionHint, {1.f, 0.f}));

        hud.pauseSelectHint.setString("Select [Enter]");
        hud.pauseSelectHint.setFont(font);
        hud.pauseSelectHint.setCharacterSize(16);
        hud.pauseSelectHint.setFillColor(sf::Color::White);
        hud.pauseSelectHint.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING + 30.f);
        hud.pauseSelectHint.setOrigin(GetTextOrigin(hud.pauseSelectHint, {1.f, 0.f}));

        int index = 0;
        for (auto& option : hud.pauseOptions)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(font);
            option.second.textNode.setCharacterSize(20);
            option.second.textNode.setFillColor(hud.pauseSelectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

            index++;
        }
    }

    void DrawPause(sf::RenderWindow& window, const HUD& hud)
    {
        window.draw(hud.pauseTitle);
        window.draw(hud.pauseToggleOptionHint);
        window.draw(hud.pauseSelectHint);

        for (auto& option : hud.pauseOptions)
        {
            window.draw(option.second.textNode);
        }
    }

    void PauseKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                PauseOptionSelectHandler(window, game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MenuToggleOption(game.hud.pauseOptions, game.hud.pauseSelectedOptionKey, MenuDirectionMovement::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MenuToggleOption(game.hud.pauseOptions, game.hud.pauseSelectedOptionKey, MenuDirectionMovement::Down);
            }
        }
    }

    void PauseOptionSelectHandler(sf::RenderWindow& window, Game& game)
    {
        switch (game.hud.pauseSelectedOptionKey)
        {
        case PauseOptionKey::Continue:
            PopGameState(game);
            break;
        case PauseOptionKey::ExitToMenu:
            RestartGame(game);
            break;
        default:
            break;
        }
    }

    void SetPauseOptionKey(HUD& hud, const PauseOptionKey& newKey)
    {
        if (hud.pauseOptions.empty()) return;

        const auto it = hud.pauseOptions.find(newKey);
        if (it == hud.pauseOptions.end()) return;

        hud.pauseSelectedOptionKey = newKey;
        for (auto& option : hud.pauseOptions)
        {
            option.second.textNode.setFillColor(option.first == newKey ? sf::Color::Green : sf::Color::White);
        }
    }
}
