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
        float speed = PLAYER_INITIAL_SPEED;
        PlayerDirection direction = PlayerDirection::Right;
        sf::Sprite sprite;
        std::string name = "You";
    };


    void InitPlayer(Player& player, const sf::Texture& texture);

    bool HasPlayerCollisionWithWindowBorder(const Position2D& position);

    void UpdatePlayerMovement(Player& player, const float& time);

    void UpdateFaceRotation(Player& player);

    void DrawPlayer(Player& player, sf::RenderWindow& window);
}
