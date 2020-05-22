#include "RotationHandler.h"

#define ROTATION_PER_FRAME 10 
RotationHandler::RotationHandler(World* world){
    RotationHandler::world = world;
    start = false;
    Rotate=ROTATION_PER_FRAME;
}

RotationHandler::~RotationHandler(){
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
    std::vector<Object*> mainObjects = world->getMainObject();
    AngleRotation rot(0,Rotate,0);
    for(Object * object : mainObjects){
        object->rotate(rot);
    }
}

void RotationHandler::rotateLeft(){
    std::vector<Object*> mainObjects = world->getMainObject();
    AngleRotation rot(0,-Rotate,0);
    for(Object * object : mainObjects){
        object->rotate(rot);
    }

}
void RotationHandler::rotateUp(){
    std::vector<Object*> mainObjects = world->getMainObject();
    AngleRotation rot(Rotate,0,0);
    for(Object * object : mainObjects){
        object->rotate(rot);
    }
}
void RotationHandler::rotateDown(){
    std::vector<Object*> mainObjects = world->getMainObject();
    AngleRotation rot(-Rotate,0,0);
    for(Object * object : mainObjects){
        object->rotate(rot);
    }
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