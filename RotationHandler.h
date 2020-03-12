#include "World.h"
#include "GL/glut.h"

class RotationHandler{
    public:
        RotationHandler(World* w);
        void Start();
        void Stop();
        ~RotationHandler();
    private:
        static void keyboardHandler(int key,int x, int y);

        static void rotateRight();
        static void rotateUp();
        static void rotateLeft();
        static void rotateDown();

    private:
        static World* world;
}