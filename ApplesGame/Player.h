#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
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
        float speed = INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::RectangleShape texture;
    };

    void InitPlayer(Player& player);

    bool HasPlayerCollisionWithWindowBorder(const Position2D& position);

    void UpdatePlayerMovement(Player& player, const float& time);
}
