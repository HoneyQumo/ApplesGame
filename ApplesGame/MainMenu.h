#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Leaderboard.h"


namespace ApplesGame
{
    enum class ToggleMenuDirection
    {
        Up = 0,
        Down,
    };

    enum class MainMenuOptionKey
    {
        StartGame = 0,
        Leaderboard,
        Settings,
        Exit
    };

    struct MainMenuOption
    {
        std::string title;
        sf::Text textNode;
    };

    struct MainMenu
    {
        std::map<MainMenuOptionKey, MainMenuOption> options = {
            {MainMenuOptionKey::StartGame, {"Start Game", {}}},
            {MainMenuOptionKey::Leaderboard, {"Leaderboard", {}}},
            {MainMenuOptionKey::Settings, {"Settings", {}}},
            {MainMenuOptionKey::Exit, {"Exit", {}}},
        };

        MainMenuOptionKey selectedOptionKey;


        sf::Text title;
        sf::Text hintExit;
        sf::Text hintReturnBack;

        sf::Text modeSettingsTitle;
        sf::Text isInfiniteMode;
        sf::Text isAcceleratedMode;

        sf::Text leaderboardTitle;
        std::vector<sf::Text> leaderboardVector;
    };

    struct Game;

    void InitMainMenu(Game& game);
    void DrawMainMenu(sf::RenderWindow& window, const MainMenu& mainMenu);

    void InitLeaderboard(Game& game);
    void DrawLeaderboard(sf::RenderWindow& window, const MainMenu& mainMenu);

    void InitSettings(Game& game);
    void UpdateSettings(Game& game);
    void DrawSettings(sf::RenderWindow& window, const MainMenu& mainMenu);
    void SettingsKeyboardHandler(const sf::Event& event, Game& game);

    void MainMenuKeyboardHandler(sf::RenderWindow& window, const sf::Event& event, Game& game);
    void MainMenuToggleOption(std::map<MainMenuOptionKey, MainMenuOption>& options, MainMenuOptionKey& selectedOptionKey, ToggleMenuDirection direction);
    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game);
}
