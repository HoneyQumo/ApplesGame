// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const std::string RESOURCES_PATH = "Resources/";
constexpr int SCREEN_WIDTH = 800;
constexpr int SCREEN_HEIGHT = 600;
constexpr float INITIAL_SPEED = 100.f;
constexpr float PLAYER_SIZE = 20.f;
constexpr float ACCELERATION = 20.f;
constexpr int TOTAL_APPLES = 20;
constexpr float APPLE_SIZE = 20.f;
// constexpr float HALF_COLLIDERS_SUM = (PLAYER_SIZE + APPLE_SIZE) / 2.f;
constexpr float SQUARE_RADIUS_SUM = (APPLE_SIZE + PLAYER_SIZE) * (APPLE_SIZE + PLAYER_SIZE) / 4.f;

float floatRandom(const float a, const float b)
{
    return a + rand() / static_cast<float>(RAND_MAX) * (b - a);
}

int main()
{
    int seed = static_cast<int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");
    float playerX = SCREEN_WIDTH / 2.f;
    float playerY = SCREEN_HEIGHT / 2.f;
    float playerSpeed = INITIAL_SPEED;
    /*
     * 0 - right 
     * 1 - up
     * 2 - left
     * 3 - down
     */
    int playerDirection = 0;

    sf::RectangleShape playerShape;
    playerShape.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    playerShape.setFillColor(sf::Color::Red);
    playerShape.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    playerShape.setPosition(playerX, playerY);

    /* Init apples */
    float applesX[TOTAL_APPLES];
    float applesY[TOTAL_APPLES];
    bool isAppleEaten[TOTAL_APPLES];
    sf::CircleShape applesShape[TOTAL_APPLES];

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        isAppleEaten[i] = false;

        applesX[i] = floatRandom(0, SCREEN_WIDTH);
        applesY[i] = floatRandom(0, SCREEN_HEIGHT);

        applesShape[i].setRadius(APPLE_SIZE / 2.f);
        applesShape[i].setFillColor(sf::Color::Green);
        applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
        applesShape[i].setPosition(applesX[i], applesY[i]);
    }

    int numEatenApples = 0;

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
                window.close();
        }

        /* Set player direction */
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerDirection = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerDirection = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerDirection = 2;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerDirection = 3;
        }

        playerSpeed += ACCELERATION * deltaTime;

        /* Update player state */
        if (playerDirection == 0)
        {
            playerX += playerSpeed * deltaTime;
        }
        else if (playerDirection == 1)
        {
            playerY -= playerSpeed * deltaTime;
        }
        else if (playerDirection == 2)
        {
            playerX -= playerSpeed * deltaTime;
        }
        else if (playerDirection == 3)
        {
            playerY += playerSpeed * deltaTime;
        }

        const bool hasTopCollision = playerY - PLAYER_SIZE / 2.f < 0.f;
        const bool hasLeftCollision = playerX - PLAYER_SIZE / 2.f < 0.f;
        const bool hasRightCollision = playerX + PLAYER_SIZE / 2.f > SCREEN_WIDTH;
        const bool hasBottomCollision = playerY + PLAYER_SIZE / 2.f > SCREEN_HEIGHT;

        if (hasTopCollision || hasRightCollision || hasBottomCollision || hasLeftCollision)
        {
            window.close();
            break;
        }

        for (int i = 0; i < TOTAL_APPLES; ++i)
        {
            if (!isAppleEaten[i])
            {
                /* Check collisions for squares */
                // float deltaX = fabs(playerX - applesX[i]);
                // float deltaY = fabs(playerY - applesY[i]);
                // if (deltaX <= HALF_COLLIDERS_SUM && deltaY <= HALF_COLLIDERS_SUM)
                // {
                //     isAppleEaten[i] = true;
                //     ++numEatenApples;
                // }

                /* Check collisions for circles */
                float cathetusX = static_cast<float>(pow(playerX - applesX[i], 2));
                float cathetusY = static_cast<float>(pow(playerY - applesY[i], 2));
                float hypotenuse = cathetusX + cathetusY;
                if (hypotenuse <= SQUARE_RADIUS_SUM)
                {
                    /* Hide 'eaten' apple */
                    isAppleEaten[i] = true;
                    ++numEatenApples;

                    /* Init new apple */
                    isAppleEaten[i] = false;
                    applesX[i] = floatRandom(0, SCREEN_WIDTH);
                    applesY[i] = floatRandom(0, SCREEN_HEIGHT);
                    applesShape[i].setRadius(APPLE_SIZE / 2.f);
                    applesShape[i].setFillColor(sf::Color::Green);
                    applesShape[i].setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
                    applesShape[i].setPosition(applesX[i], applesY[i]);
                }
            }
        }

        /* Endgame condition */
        // if (numEatenApples == TOTAL_APPLES)
        // {
        //     window.close();
        //     break;
        // }

        window.clear();
        playerShape.setPosition(playerX, playerY);
        for (int i = 0; i < TOTAL_APPLES; ++i)
        {
            if (!isAppleEaten[i])
            {
                window.draw(applesShape[i]);
            }
        }
        window.draw(playerShape);
        window.display();
    }

    return 0;
}
