#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

namespace ApplesGame
{
    struct Apple
    {
        Position2D position;
        sf::CircleShape texture;
    };

    void InitApple(Apple& apple);
}
