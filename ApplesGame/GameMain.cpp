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

Position2D getRandomPositionInScreen()
{
    return Position2D{
        GetFloatInRange(0, SCREEN_WIDTH),
        GetFloatInRange(0, SCREEN_HEIGHT)
    };
}

void InitApple(Apple& apple)
{
    apple.position = getRandomPositionInScreen();
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

/* Check collisions for squares */
// Example:  if (isRectangleCollide(playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, applePosition, { APPLE_SIZE, APPLE_SIZE }))
bool isRectangleCollide(
    const Position2D& position1, const Vector2D& size1,
    const Position2D& position2, const Vector2D& size2
)
{
    float halfColliderSumX = (size1.x + size2.x) / 2.f;
    float halfColliderSumY = (size1.y + size2.y) / 2.f;

    float deltaX = fabs(position1.x - position2.x);
    float deltaY = fabs(position1.y - position2.y);

    return deltaX <= halfColliderSumX && deltaY <= halfColliderSumY;
}

bool isCircleCollide(
    const Position2D& position1, const float& radius1,
    const Position2D& position2, const float& radius2
)
{
    float cathetusX = static_cast<float>(pow(position1.x - position2.x, 2));
    float cathetusY = static_cast<float>(pow(position1.y - position2.y, 2));
    float hypotenuse = cathetusX + cathetusY;

    float squareRadiusSum = (radius1 + radius2) * (radius1 + radius2);

    return hypotenuse <= squareRadiusSum;
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


void InitGame(GameState& gameState)
{
    gameState.player.position.x = SCREEN_WIDTH / 2.f;
    gameState.player.position.y = SCREEN_HEIGHT / 2.f;
    gameState.player.speed = INITIAL_SPEED;
    gameState.player.direction = PlayerDirection::Right;

    gameState.player.texture.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
    gameState.player.texture.setFillColor(sf::Color::Red);
    gameState.player.texture.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
    gameState.player.texture.setPosition(gameState.player.position.x, gameState.player.position.y);

    gameState.numEatenApples = 0;

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        InitApple(gameState.apple[i]);
    }
}

void UpdateGame(GameState& gameState, const float& time)
{
    /* Set player direction */
    KeyboardHandler(gameState.player.direction);

    UpdatePlayerMovement(gameState.player, time);

    if (HasPlayerCollisionWithWindowBorder(gameState.player.position))
    {
        /* Pause GAME LOOP */
        std::this_thread::sleep_for(std::chrono::seconds(1));

        /* Reset game */
        InitGame(gameState);
    }

    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        if (isCircleCollide(
                gameState.player.position, PLAYER_SIZE / 2.f,
                gameState.apple[i].position, APPLE_SIZE / 2.f)
        )
        {
            /* Count eated apples */
            ++gameState.numEatenApples;

            /* Init new apple */
            InitApple(gameState.apple[i]);

            gameState.player.speed += ACCELERATION;
        }
    }
}

void DrawGame(sf::RenderWindow& window, GameState& gameState)
{
    window.clear();


    gameState.player.texture.setPosition(gameState.player.position.x, gameState.player.position.y);
    for (int i = 0; i < TOTAL_APPLES; ++i)
    {
        window.draw(gameState.apple[i].texture);
    }
    window.draw(gameState.player.texture);

    window.display();
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

        UpdateGame(gameState, deltaTime);

        DrawGame(window, gameState);
    }

    return 0;
}
