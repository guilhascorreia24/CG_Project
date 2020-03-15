#include "Object.h"
#include "stdio.h"

void Object::rotate(AngleRotation& rot){
    this->rot += &rot;
}

void Object::draw(){
    glRotatef(rot.z,1,0,0);
    glRotatef(rot.y,0,1,0);
    glRotatef(rot.x,0,0,1);
    printf("Rotation: Angle: %f - X: %f - Y: %f - Z: %f\n",rot.x,rot.y,rot.z);
    drawShape();
}

Object::Object() : rot(0,0,0){
}

Object::~Object(){
}




Cube::Cube(){
    arr = (Point*)malloc(sizeof(Point) * 8);
    arr[0] = Point(1,1,-1);     //H
    arr[1] = Point(-1,1,-1);    //G
    arr[2] = Point(-1,-1,-1);   //F
    arr[3] = Point(1,-1,-1);    //E

    arr[4] = Point(1,1,1);      //D
    arr[5] = Point(-1,1,1);     //C
    arr[6] = Point(-1,-1,1);    //B
    arr[7] = Point(1,-1,1);     //A
}

Cube::~Cube(){
    free(arr);
}

void Cube::drawShape(){
//Under face
    glColor3f(255,255,255);
    glBegin(GL_QUADS);
        //Under
        glVertex3f(arr[0].x,arr[0].y,arr[0].z);
        glVertex3f(arr[1].x,arr[1].y,arr[1].z);
        glVertex3f(arr[2].x,arr[2].y,arr[2].z);
        glVertex3f(arr[3].x,arr[3].y,arr[3].z);
    glEnd();
    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        //Above
        glVertex3f(arr[4].x,arr[4].y,arr[4].z);
        glVertex3f(arr[5].x,arr[5].y,arr[5].z);
        glVertex3f(arr[6].x,arr[6].y,arr[6].z);
        glVertex3f(arr[7].x,arr[7].y,arr[7].z);
    glEnd();

    glColor3f(255,255,255);
    glBegin(GL_QUADS);
        //Right
        glVertex3f(arr[0].x,arr[0].y,arr[0].z);
        glVertex3f(arr[4].x,arr[4].y,arr[4].z);
        glVertex3f(arr[5].x,arr[5].y,arr[5].z);
        glVertex3f(arr[1].x,arr[1].y,arr[1].z);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        //Back
        glVertex3f(arr[1].x,arr[1].y,arr[1].z);
        glVertex3f(arr[2].x,arr[2].y,arr[2].z);
        glVertex3f(arr[6].x,arr[6].y,arr[6].z);
        glVertex3f(arr[5].x,arr[5].y,arr[5].z);
    glEnd();
    glColor3f(255,255,255);

    glBegin(GL_QUADS);
        //Left
        glVertex3f(arr[7].x,arr[7].y,arr[7].z);
        glVertex3f(arr[4].x,arr[4].y,arr[4].z);
        glVertex3f(arr[2].x,arr[2].y,arr[2].z);
        glVertex3f(arr[3].x,arr[3].y,arr[3].z);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_QUADS);
        //Front
        glVertex3f(arr[7].x,arr[7].y,arr[7].z);
        glVertex3f(arr[6].x,arr[6].y,arr[6].z);
        glVertex3f(arr[0].x,arr[0].y,arr[0].z);
        glVertex3f(arr[3].x,arr[3].y,arr[3].z);
    glEnd();

}