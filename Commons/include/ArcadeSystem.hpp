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

    static const int ArrowLeft = -2;
    //113;'q'
    static const int ArrowRight = -3;
    //261;'d'
    static const int ArrowUp = -4;
    //259;'z'
    static const int ArrowDown = -5;
    //258;'s'
    static const int Space = ' ';//' '

    static const int PrevGraph = -7; // '2'
    static const int NextGraph = -8; //'3'
    static const int PrevGame = -9; //'4'
    static const int NextGame = -10; //'5'
    static const int Restart = -11; //'8'
    static const int Home = -12; //'9'
    static const int Exit = -13; //27
    static const int Pause = 'p'; //'P'
    static const int Enter = -15;
    static const int Backspace = -16;
};

#endif //C_ARCADESYSTEM_HPP
