#include "Constants.h"
#include "Sounds.h"

namespace ApplesGame
{
    void InitSounds(GameSound& audio, const GameSoundBuffer& buffer)
    {
        audio.playerDeath.setBuffer(buffer.playerDeath);
        audio.appleEat.setBuffer(buffer.appleEat);

        audio.playerDeath.setVolume(INITIAL_VOLUME);
        audio.appleEat.setVolume(INITIAL_VOLUME);
    }
}
