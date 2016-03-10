//
// Created by veyrie_f on 3/9/16.
//

#include <iostream>
#include "Window.hpp"

int main(int ac, char **av)
{
    Window w;
    SDL_Event event;
    bool _continue = true;

    while (_continue)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    _continue = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        _continue = false;
                    break;
                case SDL_KEYUP:
                    break;
                case SDL_MOUSEMOTION:
                    break;
                case SDL_MOUSEBUTTONUP:
                case SDL_MOUSEBUTTONDOWN:
                    break;
            }
        }
        w.RefreshImage();
    }
    return 0;
}