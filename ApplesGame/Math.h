#pragma once
#include <cmath>

namespace ApplesGame
{
    struct Vector2D
    {
        float x = 0.f;
        float y = 0.f;
    };

    using Position2D = Vector2D;

    float GetFloatInRange(float a, float b);

    Position2D getRandomPositionInScreen(float screenWidth, float screenHeight);

    /* Check collisions for squares */
    /* Example:  if (
     *      isRectangleCollide(playerPosition, { PLAYER_SIZE, PLAYER_SIZE }, 
     *      applePosition, { APPLE_SIZE, APPLE_SIZE })
     * ) */
    bool isRectangleCollide(
        const Position2D& position1, const Vector2D& size1,
        const Position2D& position2, const Vector2D& size2
    );

    bool isCircleCollide(
        const Position2D& position1, const float& radius1,
        const Position2D& position2, const float& radius2
    );
}
