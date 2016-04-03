//
// Created by veyrie_f on 3/30/16.
//

#include <iostream>
#include "Sound.hpp"
#include "../Exception/LoadException.hpp"
#include "../Graphique/SDL2/include/SDL.h"

// Redefine the static member to avoid undefined symbols in dynaic linking
Sound * Sound::m_sound_token;

// Callback called by Mix when a channels ends playing
void Sound::ChunkCallback(int channel)
{
    Sound::Instance()->SoundFinished(channel);
}

Sound::Sound()
{
    if (SDL_Init(SDL_INIT_AUDIO) == -1)
    {
        throw arcade::InitRenderException("SDL audio");
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        throw arcade::InitRenderException("SDL audio");
    }
    m_sound_token = this;
    Mix_ChannelFinished(ChunkCallback);
}

Sound::~Sound()
{
    for (auto var : m_jukebox)
    {
        Mix_FreeChunk(var.second);
    }
    SDL_CloseAudio();
    Mix_CloseAudio();
}

/// Plays a sound located at path.
/// If bLoop, loops forever.
/// If bOverlap, is the sound is already playing kills the song and restarts it
/// If bStop, stops the sound
void Sound::PlaySound(std::string const &soundPath, bool bLoop, bool bOverlap, bool bStop)
{
    int channel = 0;
    Mix_Chunk *music;

    if (bStop)
    {
        if (m_sounds.find(soundPath) != m_sounds.end())
        {
            StopSound(soundPath);
        }
    }
    else
    {
        if (m_jukebox.find(soundPath) == m_jukebox.end())
        {
            m_jukebox[soundPath] = Mix_LoadWAV(soundPath.c_str());
        }
        music = m_jukebox[soundPath];

        if (music != NULL)
        {
            if (m_sounds.find(soundPath) == m_sounds.end())
            {
                channel = Mix_PlayChannel(-1, music, (bLoop) ? -1 : 0);
                m_sounds[soundPath] = channel;
            }
            else if (bOverlap)
            {
                StopSound(soundPath);
                channel = Mix_PlayChannel(-1, music, (bLoop) ? -1 : 0);
                m_sounds[soundPath] = channel;
            }
        }
    }
}

/// Called when a sound finishes
void Sound::SoundFinished(int channel)
{
    for (std::map<std::string, int>::iterator it = m_sounds.begin(); it != m_sounds.end(); ++it)
    {
        if (it->second == channel)
        {
            m_sounds.erase(it);
            break;
        }
    }
}

void Sound::StopSound(std::string const &soundPath)
{
    if (m_sounds.find(soundPath) != m_sounds.end())
    {
        Mix_HaltChannel(m_sounds[soundPath]);
    }
}
