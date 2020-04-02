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
        case GLUT_KEY_DOWN:
            glLoadIdentity();
            rotateDown();
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            glLoadIdentity();
            rotateUp();
            glutPostRedisplay();
            break;

        case GLUT_KEY_LEFT:
            glLoadIdentity();
            rotateLeft();
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            glLoadIdentity();
            rotateRight();
            glutPostRedisplay();
            break;
        default:
        break;
    }
}

void RotationHandler::keyboardSpeed(unsigned char key, int x,int y){
    if(!start){return;}
    switch(key){
        case 'a':
        //printf("%d\n",Rotate);
            glLoadIdentity();
            moreSpeed();
            glutPostRedisplay();
            break;
        case 'z':
        //printf("%d\n",Rotate);
            glLoadIdentity();
            lessSpeed();
            glutPostRedisplay();
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