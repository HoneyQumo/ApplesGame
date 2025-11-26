#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame
{
    struct GameSoundBuffer
    {
        sf::SoundBuffer appleEat;
        sf::SoundBuffer playerDeath;
    };

    struct GameSound
    {
        sf::Sound appleEat;
        sf::Sound playerDeath;
    };

    void InitSounds(GameSound& audio, const GameSoundBuffer& buffer);
}
