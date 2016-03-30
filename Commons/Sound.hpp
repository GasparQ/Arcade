//
// Created by veyrie_f on 3/30/16.
//

#ifndef CPP_ARCADE_SOUND_HPP
#define CPP_ARCADE_SOUND_HPP

#include <map>
#include "include/AComponent.hpp"

class Sound : public AComponent
{
public:
    Sound();
    virtual ~Sound();

public:
    void PlaySound(std::string const& soundPath, bool bLoop);

private:
    class SoundObj
    {
    public:
        SoundObj(std::string const& path, bool bLoop);
        ~SoundObj();
    };

private:
    std::map<std::string, SoundObj> m_sounds;
};


#endif //CPP_ARCADE_SOUND_HPP
