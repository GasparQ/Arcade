//
// Created by gaspar_q on 3/13/16.
//

#ifndef C_ARCADESYSTEM_HPP
#define C_ARCADESYSTEM_HPP

#include <stddef.h>

namespace ArcadeSystem
{
    static const size_t winWidth = 50;
    static const size_t winHeight = 30;

    static const int ArrowLeft = 0;
    //113;'q'
    static const int ArrowRight = 1;
    //261;'d'
    static const int ArrowUp = 2;
    //259;'z'
    static const int ArrowDown = 3;
    //258;'s'
    static const int Space = 4;//' '

    static const int PrevGraph = 5; // '2'
    static const int NextGraph = 6; //'3'
    static const int PrevGame = 7; //'4'
    static const int NextGame = 8; //'5'
    static const int Restart = 9; //'8'
    static const int Home = 10; //'9'
    static const int Exit = 11; //27
    static const int Pause = 12; //'P'
};

#endif //C_ARCADESYSTEM_HPP
