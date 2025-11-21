// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <cmath>
#include <thread>

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

struct Vector2D
{
    float x = 0.f;
    float y = 0.f;
};

using Position2D = Vector2D;

enum class PlayerDirection
{
    Right = 0,
    Up = 1,
    Left = 2,
    Down = 3
};

struct Player
{
    Position2D position;
    float speed = 0.f;
    PlayerDirection direction = PlayerDirection::Right;
    sf::RectangleShape texture;
};

struct Apple
{
    Position2D position;
    sf::CircleShape texture;
};

struct GameState
{
    Player player;
    Apple apple[TOTAL_APPLES];
    int numEatenApples = 0;
};

float GetFloatInRange(const float a, const float b)
{
    return a + rand() / static_cast<float>(RAND_MAX) * (b - a);
}

void InitApple(Apple& apple)
{
    apple.position.x = GetFloatInRange(0, SCREEN_WIDTH);
    apple.position.y = GetFloatInRange(0, SCREEN_HEIGHT);

    apple.texture.setRadius(APPLE_SIZE / 2.f);
    apple.texture.setFillColor(sf::Color::Green);
    apple.texture.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
    apple.texture.setPosition(apple.position.x, apple.position.y);
}

void UpdatePlayerMovement(Player& player, const float& time)
{
    /* Update player state */
    switch (player.direction)
    {
    case PlayerDirection::Right:
        {
            player.position.x += player.speed * time;
            break;
        }
    case PlayerDirection::Up:
        {
            player.position.y -= player.speed * time;
            break;
        }
    case PlayerDirection::Left:
        {
            player.position.x -= player.speed * time;
            break;
        }
    case PlayerDirection::Down:
        {
            player.position.y += player.speed * time;
            break;
        }
    }
}

bool HasPlayerCollisionWithWindowBorder(const Position2D& position)
{
    const bool hasTopCollision = position.y - PLAYER_SIZE / 2.f < 0.f;
    const bool hasLeftCollision = position.x - PLAYER_SIZE / 2.f < 0.f;
    const bool hasRightCollision = position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH;
    const bool hasBottomCollision = position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT;

    return hasTopCollision || hasRightCollision || hasBottomCollision || hasLeftCollision;
}

bool HasPlayerCollisionWithApple(const Position2D& playerPosition, const Position2D& applePosition)
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
    float cathetusX = static_cast<float>(pow(playerPosition.x - applePosition.x, 2));
    float cathetusY = static_cast<float>(pow(playerPosition.y - applePosition.y, 2));
    float hypotenuse = cathetusX + cathetusY;
    return hypotenuse <= SQUARE_RADIUS_SUM;
}

void KeyboardHandler(PlayerDirection& playerDirection)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerDirection = PlayerDirection::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerDirection = PlayerDirection::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerDirection = PlayerDirection::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerDirection = PlayerDirection::Down;
    }
}

void InitGame(GameState& state)
{
    state.player.position.x = SCREEN_WIDTH / 2.f;
    state.player.position.y = SCREEN_HEIGHT / 2.f;
    state.player.speed = INITIAL_SPEED;
    state.player.direction = PlayerDirection::Right;

    state.player.texture.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    state.player.texture.setFillColor(sf::Color::Red);
    state.player.texture.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    state.player.texture.setPosition(state.player.position.x, state.player.position.y);

    state.numEatenApples = 0;

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        InitApple(state.apple[i]);
    }
}


int main()
{
    int seed = static_cast<int>(time(nullptr));
    srand(seed);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game");

    /* Init game */
    GameState gameState;
    InitGame(gameState);

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

        /* Set player direction */
        KeyboardHandler(gameState.player.direction);

        UpdatePlayerMovement(gameState.player, deltaTime);

        if (HasPlayerCollisionWithWindowBorder(gameState.player.position))
        {
            /* Pause GAME LOOP */
            std::this_thread::sleep_for(std::chrono::seconds(1));

            /* Reset game */
            InitGame(gameState);
        }

        for (int i = 0; i < TOTAL_APPLES; ++i)
        {
            if (HasPlayerCollisionWithApple(gameState.player.position, gameState.apple[i].position))
            {
                /* Count eated apples */
                ++gameState.numEatenApples;

                /* Init new apple */
                InitApple(gameState.apple[i]);

                gameState.player.speed += ACCELERATION;
            }
        }

        window.clear();
        gameState.player.texture.setPosition(gameState.player.position.x, gameState.player.position.y);
        for (int i = 0; i < TOTAL_APPLES; ++i)
        {
            window.draw(gameState.apple[i].texture);
        }
        window.draw(gameState.player.texture);
        window.display();
    }

    return 0;
}
