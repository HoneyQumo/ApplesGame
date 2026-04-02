#include "Game.h"

namespace ApplesGame
{
    void InitMainMenu(Game& game)
    {
        MainMenu& mainMenu = game.mainMenuScreen;
        mainMenu.selectedOptionKey = MainMenuOptionKey::StartGame;

        mainMenu.title.setString("MAIN MENU");
        mainMenu.title.setFont(game.font);
        mainMenu.title.setStyle(sf::Text::Underlined);
        mainMenu.title.setCharacterSize(48);
        mainMenu.title.setFillColor(sf::Color::White);
        mainMenu.title.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        mainMenu.title.setOrigin(GetTextOrigin(mainMenu.title, {0.5f, 1.f}));

        int index = 0;
        for (auto& option : mainMenu.options)
        {
            option.second.textNode.setString(option.second.title);
            option.second.textNode.setFont(game.font);
            option.second.textNode.setCharacterSize(20);
            option.second.textNode.setFillColor(mainMenu.selectedOptionKey == option.first ? sf::Color::Green : sf::Color::White);
            option.second.textNode.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            option.second.textNode.setOrigin(GetTextOrigin(option.second.textNode, {0.5f, 0.5f}));

            index++;
        }

        mainMenu.hintExit.setString("Exit [ESC]");
        mainMenu.hintExit.setFont(game.font);
        mainMenu.hintExit.setCharacterSize(16);
        mainMenu.hintExit.setFillColor(sf::Color::White);
        mainMenu.hintExit.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        mainMenu.hintExit.setOrigin(GetTextOrigin(mainMenu.hintExit, {1.f, 0.f}));

        mainMenu.hintReturnBack.setString("Return [Backspace]");
        mainMenu.hintReturnBack.setFont(game.font);
        mainMenu.hintReturnBack.setCharacterSize(16);
        mainMenu.hintReturnBack.setFillColor(sf::Color::White);
        mainMenu.hintReturnBack.setPosition(SCREEN_WIDTH - SCREEN_PADDING, SCREEN_PADDING);
        mainMenu.hintReturnBack.setOrigin(GetTextOrigin(mainMenu.hintReturnBack, {1.f, 0.f}));
    }

    void DrawMainMenu(sf::RenderWindow& window, const MainMenu& mainMenu)
    {
        window.draw(mainMenu.title);
        window.draw(mainMenu.hintExit);

        for (const auto& option : mainMenu.options)
        {
            window.draw(option.second.textNode);
        }
    }

    void InitLeaderboard(Game& game)
    {
        /* Leaderboard */
        auto& mainMenu = game.mainMenuScreen;

        mainMenu.leaderboardTitle.setString("===== LEADERBOARD =====");
        mainMenu.leaderboardTitle.setFont(game.font);
        mainMenu.leaderboardTitle.setCharacterSize(36);
        mainMenu.leaderboardTitle.setFillColor(sf::Color::White);
        mainMenu.leaderboardTitle.setPosition(SCREEN_WIDTH / 2.f, OFFSET_TOP_WINDOW_10_PERCENT);
        mainMenu.leaderboardTitle.setOrigin(GetTextOrigin(mainMenu.leaderboardTitle, {0.5f, 1.f}));

        mainMenu.leaderboardVector.clear();
        std::vector<LeaderboardPositionPair> tmpSortedLeaderboard = GetSortedLeaderboardArray(game.leaderboard);

        int index = 0;
        for (const auto& item : tmpSortedLeaderboard)
        {
            sf::Text tmpItem;
            tmpItem.setString(item.first + " - " + std::to_string(item.second));
            tmpItem.setFont(game.font);
            tmpItem.setCharacterSize(20);
            tmpItem.setFillColor(item.first == "You" ? sf::Color::Yellow : sf::Color::White);
            tmpItem.setPosition(SCREEN_PADDING, OFFSET_TOP_WINDOW_20_PERCENT + (index * 30.f));
            tmpItem.setOrigin(GetTextOrigin(tmpItem, {0.f, 0.5f}));

            index++;

            mainMenu.leaderboardVector.push_back(tmpItem);
        }
    }

    void DrawLeaderboard(sf::RenderWindow& window, const MainMenu& mainMenu)
    {
        window.draw(mainMenu.hintReturnBack);

        window.draw(mainMenu.leaderboardTitle);
        for (const sf::Text& item : mainMenu.leaderboardVector)
        {
            window.draw(item);
        }
    }

    void InitSettings(Game& game)
    {
        auto& mainMenu = game.mainMenuScreen;

        mainMenu.modeSettingsTitle.setString("Game settings: ");
        mainMenu.modeSettingsTitle.setFont(game.font);
        mainMenu.modeSettingsTitle.setCharacterSize(24);
        mainMenu.modeSettingsTitle.setFillColor(sf::Color::White);
        mainMenu.modeSettingsTitle.setPosition(SCREEN_PADDING, SCREEN_PADDING);
        mainMenu.modeSettingsTitle.setOrigin(GetTextOrigin(mainMenu.modeSettingsTitle, {0.f, 0.f}));

        mainMenu.isInfiniteMode.setString("[1] Infinite: ");
        mainMenu.isInfiniteMode.setFont(game.font);
        mainMenu.isInfiniteMode.setCharacterSize(24);
        mainMenu.isInfiniteMode.setFillColor(sf::Color::White);
        mainMenu.isInfiniteMode.setPosition(SCREEN_PADDING, SCREEN_PADDING + 30.f);
        mainMenu.isInfiniteMode.setOrigin(GetTextOrigin(mainMenu.isInfiniteMode, {0.f, 0.f}));

        mainMenu.isAcceleratedMode.setString("[2] Acceleration: ");
        mainMenu.isAcceleratedMode.setFont(game.font);
        mainMenu.isAcceleratedMode.setCharacterSize(24);
        mainMenu.isAcceleratedMode.setFillColor(sf::Color::White);
        mainMenu.isAcceleratedMode.setPosition(SCREEN_PADDING, SCREEN_PADDING + (30.f * 2));
        mainMenu.isAcceleratedMode.setOrigin(GetTextOrigin(mainMenu.isAcceleratedMode, {0.f, 0.f}));
    }

    void UpdateSettings(Game& game)
    {
        auto& mainMenu = game.mainMenuScreen;

        if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite))
        {
            mainMenu.isInfiniteMode.setString("[1] Infinite: " + std::string("+"));
            mainMenu.isInfiniteMode.setFillColor(sf::Color::Green);
        }
        else
        {
            mainMenu.isInfiniteMode.setString("[1] Infinite: " + std::string("-"));
            mainMenu.isInfiniteMode.setFillColor(sf::Color::Red);
        }


        if (IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated))
        {
            mainMenu.isAcceleratedMode.setString("[2] Acceleration: " + std::string("+"));
            mainMenu.isAcceleratedMode.setFillColor(sf::Color::Green);
        }
        else
        {
            mainMenu.isAcceleratedMode.setString("[2] Acceleration: " + std::string("-"));
            mainMenu.isAcceleratedMode.setFillColor(sf::Color::Red);
        }
    }

    void DrawSettings(sf::RenderWindow& window, const MainMenu& mainMenu)
    {
        window.draw(mainMenu.hintReturnBack);

        window.draw(mainMenu.modeSettingsTitle);
        window.draw(mainMenu.isInfiniteMode);
        window.draw(mainMenu.isAcceleratedMode);
    }

    void SettingsKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Num1)
            {
                IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite)
                    ? DisableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite)
                    : EnableGameMode(game.mode, GameModeSettingsBitMask::IsInfinite);
            }
            else if (event.key.code == sf::Keyboard::Num2)
            {
                IsEnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated)
                    ? DisableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated)
                    : EnableGameMode(game.mode, GameModeSettingsBitMask::IsAccelerated);
            }
        }
    }

    void MainMenuKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                MainMenuOptionSelectHandler(window, game);
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                MainMenuToggleOption(game.mainMenuScreen.options, game.mainMenuScreen.selectedOptionKey, ToggleMenuDirection::Up);
            }
            else if (event.key.code == sf::Keyboard::Down)
            {
                MainMenuToggleOption(game.mainMenuScreen.options, game.mainMenuScreen.selectedOptionKey, ToggleMenuDirection::Down);
            }
        }
    }

    void MainMenuToggleOption(std::map<MainMenuOptionKey, MainMenuOption>& options, MainMenuOptionKey& selectedOptionKey, ToggleMenuDirection direction)
    {
        if (options.empty()) return;

        const auto it = options.find(selectedOptionKey);
        if (it == options.end()) return;

        if (direction == ToggleMenuDirection::Up)
        {
            if (it == options.begin())
            {
                auto prevIt = std::prev(options.end());
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                auto prevIt = std::prev(it);
                selectedOptionKey = prevIt->first;
                prevIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }
        else if (direction == ToggleMenuDirection::Down)
        {
            const auto nextIt = std::next(it);
            if (nextIt == options.end())
            {
                auto nextIt = options.begin();
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
            else
            {
                selectedOptionKey = nextIt->first;
                nextIt->second.textNode.setFillColor(sf::Color::Green);
            }
        }

        it->second.textNode.setFillColor(sf::Color::White);
    }

    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game)
    {
        switch (game.mainMenuScreen.selectedOptionKey)
        {
        case MainMenuOptionKey::StartGame:
            PopGameState(game);
            PushGameState(game, GameState::Playing);
            break;
        case MainMenuOptionKey::Leaderboard:
            // PopGameState(game);
            PushGameState(game, GameState::Leaderboard);
            break;
        case MainMenuOptionKey::Settings:
            // PopGameState(game);
            PushGameState(game, GameState::Settings);
            break;
        case MainMenuOptionKey::Exit:
            window.close();
            break;
        default:
            break;
        }
    }
}
