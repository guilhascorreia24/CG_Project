#include "Object.h"
#include <stdexcept>

bool Object::drawLabels = false;

void Object::rotate(AngleRotation& rot){
    this->rot += rot;
}

void Object::draw(){
    glPushMatrix(); 
    glTranslatef(position.x,position.y,position.z);
    glRotatef(rot.z,1,0,0);
    glRotatef(rot.y,0,1,0);
    glRotatef(rot.x,0,0,1);
    glScalef(size,size,size);
    drawShape();

    if(drawLabels){
        std::string s = getLabel();
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        glRasterPos2i(0, 5 + (h*0.0005));
        void * font = GLUT_BITMAP_9_BY_15;

        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
    }
    glPopMatrix();
}

Point Object::getPosition(){
    return position;
}
Object::Object() : position(0,0,0),rot(0,0,0),velocity(0),direction(0,0,0){
    size = 1;
}
Object::~Object(){
}

Object::Object(Point & pos, AngleRotation & rotation, Vector & direction, float velocity) : position(pos),rot(rotation) ,velocity(velocity),direction(direction){
    size = 1;
}

void Object::update(){
    Update();

    //To be fixed next version
    //Vector a = direction*velocity;
    //position += a;
}