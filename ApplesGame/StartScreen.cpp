#include "Game.h"

namespace ApplesGame
{
    void InitStartScreen(std::vector<Leaderboard>& leaderboard, StartScreen& screen, const sf::Font& font)
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

        screen.startHint.setString("Press [Space] to start");
        screen.startHint.setFont(font);
        screen.startHint.setCharacterSize(16);
        screen.startHint.setFillColor(sf::Color::White);
        screen.startHint.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - SCREEN_PADDING);
        screen.startHint.setOrigin(GetTextOrigin(screen.startHint, {0.5f, 1.f}));

        /* Settings */
        screen.modeSettingsTitle.setString("Game settings: ");
        screen.modeSettingsTitle.setFont(font);
        screen.modeSettingsTitle.setCharacterSize(24);
        screen.modeSettingsTitle.setFillColor(sf::Color::White);
        screen.modeSettingsTitle.setPosition(SCREEN_PADDING, SCREEN_PADDING);
        screen.modeSettingsTitle.setOrigin(GetTextOrigin(screen.modeSettingsTitle, {0.f, 0.f}));

        screen.isInfiniteMode.setString("[1] Infinite: ");
        screen.isInfiniteMode.setFont(font);
        screen.isInfiniteMode.setCharacterSize(24);
        screen.isInfiniteMode.setFillColor(sf::Color::White);
        screen.isInfiniteMode.setPosition(SCREEN_PADDING, SCREEN_PADDING + 30.f);
        screen.isInfiniteMode.setOrigin(GetTextOrigin(screen.isInfiniteMode, {0.f, 0.f}));

        screen.isAcceleratedMode.setString("[2] Acceleration: ");
        screen.isAcceleratedMode.setFont(font);
        screen.isAcceleratedMode.setCharacterSize(24);
        screen.isAcceleratedMode.setFillColor(sf::Color::White);
        screen.isAcceleratedMode.setPosition(SCREEN_PADDING, SCREEN_PADDING + (30.f * 2));
        screen.isAcceleratedMode.setOrigin(GetTextOrigin(screen.isAcceleratedMode, {0.f, 0.f}));

        /* Leaderboard */
        screen.leaderboardTitle.setString("===== LEADERBOARD =====");
        screen.leaderboardTitle.setFont(font);
        screen.leaderboardTitle.setCharacterSize(16);
        screen.leaderboardTitle.setFillColor(sf::Color::White);
        screen.leaderboardTitle.setPosition(SCREEN_WIDTH / 2.f, LEADERBOARD_OFFSET - 50.f);
        screen.leaderboardTitle.setOrigin(GetTextOrigin(screen.leaderboardTitle, {0.5f, 1.f}));


        for (int i = 0; i < leaderboard.size(); ++i)
        {
            Leaderboard& item = leaderboard[i];

            sf::Text tmpItem;
            tmpItem.setString(item.name + " - " + std::to_string(item.score));
            tmpItem.setFont(font);
            tmpItem.setCharacterSize(14);
            tmpItem.setFillColor(sf::Color::White);
            tmpItem.setPosition(SCREEN_WIDTH / 2.f, LEADERBOARD_OFFSET + (i * 30.f));
            tmpItem.setOrigin(GetTextOrigin(screen.leaderboardTitle, {0.5f, 1.f}));

            screen.leaderboardVector.push_back(tmpItem);
        }
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
        window.draw(screen.startHint);

        window.draw(screen.modeSettingsTitle);
        window.draw(screen.isInfiniteMode);
        window.draw(screen.isAcceleratedMode);

        window.draw(screen.leaderboardTitle);

        for (const sf::Text& item : screen.leaderboardVector)
        {
            window.draw(item);
        }
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
