#include "RotationHandler.h"

World* RotationHandler::world = NULL;

RotationHandler::RotationHandler(World* world){
    RotationHandler::world = world;
}

RotationHandler::~RotationHandler(){
    printf("Destructed\n");
    Stop();
}

void RotationHandler::Start(){
    glutSpecialFunc(keyboardHandler);
}

void RotationHandler::Stop(){
    glutSpecialFunc(NULL);
}

void RotationHandler::keyboardHandler(int key,int x, int y){
    switch(key){
        case GLUT_KEY_DOWN:
            rotateDown();
            break;
        case GLUT_KEY_UP:
            rotateUp();
            break;

        case GLUT_KEY_LEFT:
            rotateLeft();
            break;
        case GLUT_KEY_RIGHT:
            rotateRight();
            break;
    }

    glutPostRedisplay();
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