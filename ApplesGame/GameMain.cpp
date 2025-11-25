#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Game.h"

int main()
{
    using namespace ApplesGame;

    int seed = static_cast<int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

    /* Init game */
    Game game;
    InitGame(game);

    /* Init game clocks */
    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    /* GAME LOOP */
    while (window.isOpen())
    {
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                break;
            }
        }

        UpdateGame(game, deltaTime);

        window.clear();
        DrawGame(window, game);
        window.display();
    }

    return 0;
}
