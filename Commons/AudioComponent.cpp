//
// Created by veyrie_f on 3/30/16.
//

#include "AudioComponent.hpp"

AudioComponent::AudioComponent(const std::string soundPath, bool bLoop, bool bOverlap) :
        AComponent(Vector2<double>(0, 0), AComponent::COLOR_WHITE),
        m_loop(bLoop),
        m_soundPath(soundPath),
        m_overlap(bOverlap)
{

}

AudioComponent::~AudioComponent()
{

}

std::string const &AudioComponent::getSoundPath() const
{
    return m_soundPath;
}

bool AudioComponent::getLoop() const
{
    return m_loop;
}

bool AudioComponent::getOverlap() const
{
    return m_overlap;
}
