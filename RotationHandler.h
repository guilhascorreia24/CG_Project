#pragma once
#include "utils.h"
#include "World.h"

#define ROTATION_PER_FRAME 10 //Degrees

class RotationHandler{
    public:
        RotationHandler(World* w);
        void Start();
        void Stop();
        ~RotationHandler();
        void keyboardHandler(int key,int x, int y);
        void keyboardSpeed(unsigned char key, int x,int y);

        void rotateRight();
        void rotateUp();
        void rotateLeft();
        void rotateDown();


    private:

        void moreSpeed();
        void lessSpeed();

    private:
        bool start;
        World* world;
        int Rotate;
};