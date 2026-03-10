#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>

namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0.f;
        float y = 0.f;
    };

    using Position2D = Vector2D;

    float GetFloatInRange(float a, float b);

    int GetIntegerInRange(int a, int b);

    Position2D GetRandomPositionInScreen(float screenWidth, float screenHeight);

    /* Check collisions for squares */
    /* Example:  if (
     *      isRectangleCollide(playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, 
     *      applePosition, { APPLE_SIZE, APPLE_SIZE })
     * ) */
    bool IsRectangleCollide(
        const Position2D& position1, const Vector2D& size1,
        const Position2D& position2, const Vector2D& size2
    );

    bool IsCircleCollide(
        const Position2D& position1, const float& radius1,
        const Position2D& position2, const float& radius2
    );

    void SetSpriteSize(sf::Sprite& sprite, float desiredWidth, float desiredHeight);

    sf::Vector2f GetSpriteSize(const sf::Sprite& sprite, const Vector2D& desiredSize);

    void SetSpriteOrigin(sf::Sprite& sprite, float originX, float originY);

    sf::Vector2f GetTextOrigin(const sf::Text& text, const Vector2D& relativePosition);
}
