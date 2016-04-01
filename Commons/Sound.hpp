//
// Created by veyrie_f on 3/31/16.
//

#ifndef CPP_ARCADE_SOUND_HPP
#define CPP_ARCADE_SOUND_HPP

#include <map>
#include "../Graphique/SDL2_mixer/SDL_mixer.h"

// TODO:
// menu music
class Sound
{
public:
    Sound();

    virtual ~Sound();

public:
    /// Plays a song located at soundPath.
    /// @param: bLoop -> should the song loop ?
    void PlaySound(std::string const &soundPath, bool bLoop, bool bOverlap, bool bStop);

    void StopSound(std::string const&soundPath);

    static Sound *Instance()
    {
        if (m_sound_token == NULL)
        {
            m_sound_token = new Sound();
        }
        return m_sound_token;
    }

    // called when a song ends playing
    void SoundFinished(int channel);
    static void ChunkCallback(int channel);

private:
    std::map<std::string, int > m_sounds;
    static Sound *m_sound_token;
};


#endif //CPP_ARCADE_SOUND_HPP
