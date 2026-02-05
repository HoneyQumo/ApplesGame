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

        screen.isInfiniteOption.setString("[1] Infinite: ");
        screen.isInfiniteOption.setFont(font);
        screen.isInfiniteOption.setCharacterSize(16);
        screen.isInfiniteOption.setFillColor(sf::Color::White);
        screen.isInfiniteOption.setPosition(SCREEN_PADDING, SCREEN_PADDING);

        screen.isAcceleratedOption.setString("[2] Acceleration: ");
        screen.isAcceleratedOption.setFont(font);
        screen.isAcceleratedOption.setCharacterSize(16);
        screen.isAcceleratedOption.setFillColor(sf::Color::White);
        screen.isAcceleratedOption.setPosition(SCREEN_PADDING, SCREEN_PADDING + 20.f);

        screen.startHint.setString("Press [Space] to start");
        screen.startHint.setFont(font);
        screen.startHint.setCharacterSize(16);
        screen.startHint.setFillColor(sf::Color::White);
        screen.startHint.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - SCREEN_PADDING);
        screen.startHint.setOrigin(GetTextOrigin(screen.startHint, {0.5f, 1.f}));
    }

    void UpdateStartScreen(StartScreen& screen, const Game& game)
    {
        if (game.isInfinite)
        {
            screen.isInfiniteOption.setString("[1] Infinite: " + std::string("+"));
            screen.isInfiniteOption.setFillColor(sf::Color::Green);
        }
        else
        {
            screen.isInfiniteOption.setString("[1] Infinite: " + std::string("-"));
            screen.isInfiniteOption.setFillColor(sf::Color::Red);
        }


        if (game.isAccelerated)
        {
            screen.isAcceleratedOption.setString("[2] Acceleration: " + std::string("+"));
            screen.isAcceleratedOption.setFillColor(sf::Color::Green);
        }
        else
        {
            screen.isAcceleratedOption.setString("[2] Acceleration: " + std::string("-"));
            screen.isAcceleratedOption.setFillColor(sf::Color::Red);
        }
    }

    void DrawStartScreen(const StartScreen& screen, sf::RenderWindow& window)
    {
        window.draw(screen.title);
        window.draw(screen.exitHint);
        window.draw(screen.isInfiniteOption);
        window.draw(screen.isAcceleratedOption);
        window.draw(screen.startHint);
    }

    void StartScreenKeyboardHandler(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
        {
            game.isInfinite = !game.isInfinite;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
        {
            game.isAccelerated = !game.isAccelerated;
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            game.isShowStartScreen = false;
        }
    }
}
