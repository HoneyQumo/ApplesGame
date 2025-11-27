#pragma once
#include <string>

namespace ApplesGame
{
    /* Game */
    const std::string RESOURCES_PATH = "Resources/";
    constexpr int SCREEN_WIDTH = 800;
    constexpr int SCREEN_HEIGHT = 600;
    constexpr float SCREEN_PADDING = 10.f;
    constexpr float INITIAL_VOLUME = 25.f;
    constexpr int TIMEOUT_BEFORE_RESTART_IN_SECONDS = 2;
    /* Player */
    constexpr float PLAYER_INITIAL_SPEED = 100.f;
    constexpr float PLAYER_SIZE = 40.f;
    constexpr float PLAYER_ACCELERATION = 20.f;
    /* APPLES */
    constexpr int TOTAL_APPLES = 20;
    constexpr float APPLE_SIZE = 20.f;
    /* ROCKS */
    constexpr int TOTAL_ROCKS = 5;
    constexpr float ROCK_SIZE = 30.f;
}
