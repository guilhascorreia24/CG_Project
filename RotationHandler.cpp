#include "RotationHandler.h"

#define ROTATION_PER_FRAME 10 
RotationHandler::RotationHandler(World* world){
    RotationHandler::world = world;
    start = false;
    Rotate=ROTATION_PER_FRAME;
}

RotationHandler::~RotationHandler(){
    printf("Destructed\n");
    Stop();
}

void RotationHandler::Start(){
    start = true;
}

void RotationHandler::Stop(){
    start = false;
}

void RotationHandler::keyboardHandler(int key,int x, int y){
    if(!start){
        return;
    }
    switch(key){
        case 'b':
            rotateDown();
            break;
        case 'c':
            rotateUp();
            break;

        case 'e':
            rotateLeft();
            break;
        case 'd':
            rotateRight();
            break;
        default:
        break;
    }
}

void RotationHandler::keyboardSpeed(unsigned char key, int x,int y){
    if(!start){return;}
    switch(key){
        case 'a':
            moreSpeed();
            break;
        case 'z':
            lessSpeed();
            break;
    }
}

void RotationHandler::rotateRight(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(0,Rotate,0);
    mainObject->rotate(rot);
}

void RotationHandler::rotateLeft(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(0,-Rotate,0);
    mainObject->rotate(rot);

}
void RotationHandler::rotateUp(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(Rotate,0,0);
    mainObject->rotate(rot);
}
void RotationHandler::rotateDown(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(-Rotate,0,0);
    mainObject->rotate(rot);
}
void RotationHandler::moreSpeed(){
    Rotate++;
}
void RotationHandler::lessSpeed(){
    if(Rotate>0)
        Rotate--;
    else
        Rotate=0;
}