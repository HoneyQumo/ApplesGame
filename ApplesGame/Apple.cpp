#include "Apple.h"

void InitApple(Apple& apple)
{
    apple.position = getRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
    apple.texture.setRadius(APPLE_SIZE / 2.f);
    apple.texture.setFillColor(sf::Color::Green);
    apple.texture.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
    apple.texture.setPosition(apple.position.x, apple.position.y);
}
