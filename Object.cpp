#include "Object.h"
#include <stdexcept>

void Object::rotate(AngleRotation& rot){
    this->rot += rot;
}

void Object::draw(){
    glPushMatrix(); 
    glTranslatef(position.x,position.y,position.z);
    glRotatef(rot.z,1,0,0);
    glRotatef(rot.y,0,1,0);
    glRotatef(rot.x,0,0,1);
    drawShape();
    glPopMatrix();
}

Point Object::getPosition(){
    return position;
}
Object::Object() : position(0,0,0),rot(0,0,0),velocity(0),direction(0,0,0){

}
Object::~Object(){
}

Object::Object(Point & pos, AngleRotation & rotation, Vector & direction, float velocity) : position(pos),rot(rotation) ,velocity(velocity),direction(direction){
    
}

void Object::update(){
    Update();
    Vector a = direction*velocity;
    position += a;
    //printf("X: %f Y: %f, Z: %f\n",position.x,position.y,position.z);
}