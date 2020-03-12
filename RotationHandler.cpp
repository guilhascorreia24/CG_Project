#include "RotationHandler.h"

RotationHandler::RotationHandler(World* world){
    this->world = world;
}

void RotationHandler::Start(){
    glutSpecialFunc(keyboardHandler);
}

void RotationHandler::Stop(){
    glutSpecialFunc(NULL);
}

void RotationHandler::keyboardHandler(int key, int x, int y){
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
}

void RotationHandler::rotateRight(){
    Object* mainObject = world->getMainObject();

    glRotatef(15.0, 0.0, 0.0, 1.0);
}

void RotationHandler::rotateLeft(){
    Object* mainObject = world->getMainObject();

    glRotatef(15.0, 0.0, 0.0, 1.0);
}
void RotationHandler::rotateUp(){
    Object* mainObject = world->getMainObject();

    glRotatef(15.0, 0.0, 0.0, 1.0);
}
void RotationHandler::rotateDown(){
    Object* mainObject = world->getMainObject();

    glRotatef(15.0, 0.0, 0.0, 1.0);
}