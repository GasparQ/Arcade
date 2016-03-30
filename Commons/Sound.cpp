//
// Created by veyrie_f on 3/30/16.
//

#include <iostream>
#include "Sound.hpp"
#include "../Exception/LoadException.hpp"
#include "../Graphique/SDL2/include/SDL.h"
#include "../Graphique/SDL2_mixer/SDL_mixer.h"

Sound::Sound()
{
    if (SDL_Init(SDL_INIT_AUDIO) == -1)
    {
        throw arcade::InitRenderException("Error in SDL audio init");
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        throw arcade::InitRenderException("Error in SDL audio init");
    }
}

Sound::~Sound()
{
    SDL_CloseAudio();
    Mix_CloseAudio();
}

void Sound::PlaySound(std::string const &soundPath, bool bLoop)
{
    Mix_Chunk *music = Mix_LoadWAV("Doom_backsound.wav");

    if (music == NULL)
    {
        std::cerr << "Sound not found : " << soundPath << std::endl;
    }
    else
    {
        Mix_PlayChannel(-1, music, (bLoop) ? -1 : 0);
    }
}

Sound::SoundObj::SoundObj(std::string const &path, bool bLoop)
{

}

Sound::SoundObj::~SoundObj()
{

}
