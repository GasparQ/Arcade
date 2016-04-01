//
// Created by veyrie_f on 3/30/16.
//

#ifndef CPP_ARCADE_AUDIOCOMPONENT_HPP
#define CPP_ARCADE_AUDIOCOMPONENT_HPP

#include <string>
#include "include/AComponent.hpp"

class AudioComponent : public AComponent
{
public:
    AudioComponent(const std::string soundPath, bool bLoop, bool bOverlap, bool bStop);
    virtual ~AudioComponent();

    std::string const& getSoundPath() const;
    bool getLoop() const;
    bool getOverlap() const;
    bool getStop() const;

private:
    bool m_loop;
    std::string m_soundPath;
    bool m_overlap;
    bool m_stop;
};


#endif //CPP_ARCADE_AUDIOCOMPONENT_HPP
