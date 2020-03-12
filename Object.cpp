#include "Object.h"


void Object::setRotation(AngleRotation& rot){
    this->rot = rot;
}

void Object::draw(){
    glRotatef(rot.angle,rot.x,rot.y,rot.z);
    drawShape();
}