#include "RotationHandler.h"

RotationHandler::RotationHandler(World* world){
    RotationHandler::world = world;
    start = false;
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
    }

}

void RotationHandler::rotateRight(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(0,ROTATION_PER_FRAME,0);
    mainObject->rotate(rot);
}

void RotationHandler::rotateLeft(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(0,-ROTATION_PER_FRAME,0);
    mainObject->rotate(rot);

}
void RotationHandler::rotateUp(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(ROTATION_PER_FRAME,0,0);
    mainObject->rotate(rot);
}
void RotationHandler::rotateDown(){
    Object* mainObject = world->getMainObject();
    AngleRotation rot(-ROTATION_PER_FRAME,0,0);
    mainObject->rotate(rot);
}