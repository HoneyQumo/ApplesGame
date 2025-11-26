#include "Math.h"

namespace ApplesGame
{
    float GetFloatInRange(const float a, const float b)
    {
        return a + rand() / static_cast<float>(RAND_MAX) * (b - a);
    }

    Position2D GetRandomPositionInScreen(const float screenWidth, const float screenHeight)
    {
        return Position2D{
            GetFloatInRange(0, screenWidth),
            GetFloatInRange(0, screenHeight)
        };
    }

    bool IsRectangleCollide(const Position2D& position1, const Vector2D& size1, const Position2D& position2, const Vector2D& size2)
    {
        const float halfColliderSumX = (size1.x + size2.x) / 2.f;
        const float halfColliderSumY = (size1.y + size2.y) / 2.f;

        const float deltaX = fabs(position1.x - position2.x);
        const float deltaY = fabs(position1.y - position2.y);

        return deltaX <= halfColliderSumX && deltaY <= halfColliderSumY;
    }

    bool IsCircleCollide(const Position2D& position1, const float& radius1, const Position2D& position2, const float& radius2)
    {
        const float cathetusX = static_cast<float>(pow(position1.x - position2.x, 2));
        const float cathetusY = static_cast<float>(pow(position1.y - position2.y, 2));
        const float hypotenuse = cathetusX + cathetusY;

        float squareRadiusSum = (radius1 + radius2) * (radius1 + radius2);

        return hypotenuse <= squareRadiusSum;
    }

    void SetSpriteSize(sf::Sprite& sprite, const float desiredWidth, const float desiredHeight)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        const sf::Vector2f scale = {desiredWidth / spriteRect.width, desiredHeight / spriteRect.height};
        sprite.setScale(scale);
    }

    sf::Vector2f GetSpriteSize(const sf::Sprite& sprite, const Vector2D& desiredSize)
    {
        const sf::Vector2u textureSize = sprite.getTexture()->getSize();
        const sf::Vector2f scale = {desiredSize.x / static_cast<float>(textureSize.x), desiredSize.y / static_cast<float>(textureSize.y)};
        return scale;
    }

    void SetSpriteOrigin(sf::Sprite& sprite, const float originX, const float originY)
    {
        const sf::FloatRect spriteRect = sprite.getLocalBounds();
        sprite.setOrigin(originX * spriteRect.width, originY * spriteRect.height);
    }
}
