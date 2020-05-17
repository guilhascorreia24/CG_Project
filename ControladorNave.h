#pragma once
#include "utils.h"
#include "World.h"

#define ROTATION_PER_FRAME 10 //Degrees

class ControladorNave{
    public:
        ControladorNave(World* w);
        void Start();
        void Stop();
        ~ControladorNave();
        void keyboardHandler(int key,int x, int y);
        void keyboardSpeed(unsigned char key, int x,int y);
    private:

        void movimento_direita();
        void movimento_frente();
        void movimento_esquerda();
        void movimento_traz();
        // void moreSpeed();
        // void lessSpeed();

    private:
        bool start;
        World* world;
        bool colidiu;
};