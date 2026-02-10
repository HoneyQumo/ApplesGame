#include "Game.h"

namespace ApplesGame
{
    void InitStartScreen(StartScreen& screen, const sf::Font& font)
    {
        screen.title.setString("MAIN MENU");
        screen.title.setFont(font);
        screen.title.setStyle(sf::Text::Underlined);
        screen.title.setCharacterSize(48);
        screen.title.setFillColor(sf::Color::White);
        screen.title.setPosition(SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 100.f) * 10.f);
        screen.title.setOrigin(GetTextOrigin(screen.title, {0.5f, 0.5f}));

        screen.exitHint.setString("Exit [ESC]");
        screen.exitHint.setFont(font);
        screen.exitHint.setCharacterSize(16);
        screen.exitHint.setFillColor(sf::Color::White);
        screen.exitHint.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        screen.exitHint.setOrigin(GetTextOrigin(screen.exitHint, {1.f, 0.f}));

        screen.modeSettingsTitle.setString("Game settings: ");
        screen.modeSettingsTitle.setFont(font);
        screen.modeSettingsTitle.setCharacterSize(24);
        screen.modeSettingsTitle.setFillColor(sf::Color::White);
        screen.modeSettingsTitle.setPosition(SCREEN_WIDTH / 2.f, GAME_DIFFICULT_SETTING_OFFSET - 30.f);
        screen.modeSettingsTitle.setOrigin(GetTextOrigin(screen.modeSettingsTitle, {0.5f, 0.5f}));

        screen.isInfiniteMode.setString("[1] Infinite: ");
        screen.isInfiniteMode.setFont(font);
        screen.isInfiniteMode.setCharacterSize(24);
        screen.isInfiniteMode.setFillColor(sf::Color::White);
        screen.isInfiniteMode.setPosition((SCREEN_WIDTH / 2.f) - 100.f, GAME_DIFFICULT_SETTING_OFFSET);
        screen.isInfiniteMode.setOrigin(GetTextOrigin(screen.isInfiniteMode, {0.f, 0.5f}));

        screen.isAcceleratedMode.setString("[2] Acceleration: ");
        screen.isAcceleratedMode.setFont(font);
        screen.isAcceleratedMode.setCharacterSize(24);
        screen.isAcceleratedMode.setFillColor(sf::Color::White);
        screen.isAcceleratedMode.setPosition((SCREEN_WIDTH / 2.f) - 100.f, GAME_DIFFICULT_SETTING_OFFSET + 30.f);
        screen.isAcceleratedMode.setOrigin(GetTextOrigin(screen.isAcceleratedMode, {0.f, 0.5f}));

        screen.startHint.setString("Press [Space] to start");
        screen.startHint.setFont(font);
        screen.startHint.setCharacterSize(16);
        screen.startHint.setFillColor(sf::Color::White);
        screen.startHint.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - SCREEN_PADDING);
        screen.startHint.setOrigin(GetTextOrigin(screen.startHint, {0.5f, 1.f}));
    }

    void UpdateStartScreen(StartScreen& screen, const Game& game)
    {
        if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite))
        {
            screen.isInfiniteMode.setString("[1] Infinite: " + std::string("+"));
            screen.isInfiniteMode.setFillColor(sf::Color::Green);
        }
        else
        {
            screen.isInfiniteMode.setString("[1] Infinite: " + std::string("-"));
            screen.isInfiniteMode.setFillColor(sf::Color::Red);
        }


        if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated))
        {
            screen.isAcceleratedMode.setString("[2] Acceleration: " + std::string("+"));
            screen.isAcceleratedMode.setFillColor(sf::Color::Green);
        }
        else
        {
            screen.isAcceleratedMode.setString("[2] Acceleration: " + std::string("-"));
            screen.isAcceleratedMode.setFillColor(sf::Color::Red);
        }
    }

    void DrawStartScreen(const StartScreen& screen, sf::RenderWindow& window)
    {
        window.draw(screen.title);
        window.draw(screen.exitHint);
        window.draw(screen.modeSettingsTitle);
        window.draw(screen.isInfiniteMode);
        window.draw(screen.isAcceleratedMode);
        window.draw(screen.startHint);
    }

    void StartScreenKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
        {
            IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite)
                ? DisableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite)
                : EnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
        {
            IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated)
                ? DisableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated)
                : EnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            game.isShowStartScreen = false;
        }
    }
}
