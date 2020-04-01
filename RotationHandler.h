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
        static void keyboardHandler(int key,int x, int y);
    private:

        static void rotateRight();
        static void rotateUp();
        static void rotateLeft();
        static void rotateDown();

    private:
        static World* world;
};