#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Leaderboard.h"


namespace ApplesGame
{
    enum class MainMenuOptionKey
    {
        StartGame = 0,
        Leaderboard,
        Settings,
        Exit
    };

    struct MainMenu
    {
        std::map<MainMenuOptionKey, MenuOption> options = {
            {MainMenuOptionKey::StartGame, {"Start Game", {}}},
            {MainMenuOptionKey::Leaderboard, {"Leaderboard", {}}},
            {MainMenuOptionKey::Settings, {"Settings", {}}},
            {MainMenuOptionKey::Exit, {"Exit", {}}},
        };

        MainMenuOptionKey selectedOptionKey = MainMenuOptionKey::StartGame;


        sf::Text title;
        
        /* Todo: Переделать подсказки клавиш на список */
        sf::Text hintExit;
        sf::Text hintReturnBack;
        sf::Text toggleOptionHint;
        sf::Text selectHint;

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
    void MainMenuOptionSelectHandler(sf::RenderWindow& window, Game& game);
}
