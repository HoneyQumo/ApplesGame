#include "Player.h"

namespace ApplesGame
{
    void InitPlayer(Player& player)
    {
        player.position.x = SCREEN_WIDTH / 2.f;
        player.position.y = SCREEN_HEIGHT / 2.f;
        player.speed = INITIAL_SPEED;
        player.direction = PlayerDirection::Right;

        player.texture.setSize(sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE));
        player.texture.setFillColor(sf::Color::Red);
        player.texture.setOrigin(PLAYER_SIZE / 2.f, PLAYER_SIZE / 2.f);
        player.texture.setPosition(player.position.x, player.position.y);
    }

    bool HasPlayerCollisionWithWindowBorder(const Position2D& position)
    {
        const bool hasTopCollision = position.y - PLAYER_SIZE / 2.f < 0.f;
        const bool hasLeftCollision = position.x - PLAYER_SIZE / 2.f < 0.f;
        const bool hasRightCollision = position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH;
        const bool hasBottomCollision = position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT;

        return hasTopCollision || hasRightCollision || hasBottomCollision || hasLeftCollision;
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
}
