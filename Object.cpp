#include "Object.h"
#include <stdexcept>

void Object::rotate(AngleRotation& rot){
    this->rot += &rot;
}

void Object::draw(){
    glRotatef(rot.z,1,0,0);
    glRotatef(rot.y,0,1,0);
    glRotatef(rot.x,0,0,1);
    drawShape();
}

Object::Object() : rot(0,0,0){

}
Object::~Object(){
}
