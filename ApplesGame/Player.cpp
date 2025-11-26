#include "Player.h"

namespace ApplesGame
{
    void InitPlayer(Player& player, const sf::Texture& texture)
    {
        player.position.x = SCREEN_WIDTH / 2.f;
        player.position.y = SCREEN_HEIGHT / 2.f;
        player.speed = PLAYER_INITIAL_SPEED;
        player.direction = PlayerDirection::Right;

        player.sprite.setTexture(texture);
        SetSpriteSize(player.sprite, PLAYER_SIZE, PLAYER_SIZE);
        SetSpriteOrigin(player.sprite, 0.5f, 0.5f);
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

    void UpdateFaceRotation(Player& player)
    {
        // const sf::Vector2f spriteScale = player.sprite.getScale();
        const sf::Vector2f spriteScale = GetSpriteSize(player.sprite, {PLAYER_SIZE, PLAYER_SIZE});

        switch (player.direction)
        {
        case PlayerDirection::Right:
            {
                player.sprite.setScale(spriteScale.x, spriteScale.y);
                player.sprite.setRotation(0.f);
                break;
            }
        case PlayerDirection::Up:
            {
                player.sprite.setScale(spriteScale.x, spriteScale.y);
                player.sprite.setRotation(-90.f);
                break;
            }
        case PlayerDirection::Left:
            {
                player.sprite.setScale(-spriteScale.x, spriteScale.y);
                player.sprite.setRotation(0.f);
                break;
            }
        case PlayerDirection::Down:
            {
                player.sprite.setScale(spriteScale.x, spriteScale.y);
                player.sprite.setRotation(90.f);
                break;
            }
        }
    }

    void DrawPlayer(Player& player, sf::RenderWindow& window)
    {
        player.sprite.setPosition(player.position.x, player.position.y);
        window.draw(player.sprite);

        UpdateFaceRotation(player);
    }
}
