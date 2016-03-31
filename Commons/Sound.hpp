//
// Created by veyrie_f on 3/30/16.
//

#ifndef CPP_ARCADE_SOUND_HPP
#define CPP_ARCADE_SOUND_HPP

#include <map>
#include "../Graphique/SDL2_mixer/SDL_mixer.h"

class Sound
{
public:
    Sound();
    virtual ~Sound();

public:
    /// Plays a song located at soundPath.
    /// @param: bLoop -> should the song loop ?
    void PlaySound(std::string const& soundPath, bool bLoop);

private:
    std::map<std::string, Mix_Chunk*> m_sounds;
};


#endif //CPP_ARCADE_SOUND_HPP
