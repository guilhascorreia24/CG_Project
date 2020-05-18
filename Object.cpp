#include "Object.h"
#include <stdexcept>

bool Object::drawLabels = false;

void Object::rotate(AngleRotation& rot){
    this->rot += rot;
}

void Object::mover(double x, double y, double z){
    this->position.x += x;
    this->position.y += y;
    this->position.z += z;
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

Point Object::getSizeObject(){
    Point tmp = size_object;
    tmp.x=size_object.x*size;
    tmp.y=size_object.y*size;
    tmp.z=size_object.z*size;
    return tmp;
}

Point Object::getPosition(){
    return position;
}
Object::Object() : position(0,0,0),size_object(0,0,0),rot(0,0,0),velocity(0),direction(0,0,0),mass(1){
    size = 1;
}
Object::~Object(){
}

Object::Object(Point & pos, Point & size_obj,AngleRotation & rotation, Vector & direction, long double velocity, long double mass) : mass(mass),position(pos),size_object(size_obj),rot(rotation) ,velocity(velocity),direction(direction){
    size = 1;
}


void Object::update(){ 
    Update();

    // //Gravity Forces sum
    // Vector sum(0,0,0);
    // for(Object* a: gravity){
    //     Vector b = calcGravitationalForce(this,a);
    //     sum+= b;
    //     Point B = a->getPosition();
    // }
    // sum*=SPEED;


    // //Momentum
    // Vector vec = direction*velocity;
    // //printf("Object: %s -> ",getLabel());
    // //position.print();

    // sum+=vec;
    // direction=sum.unitVector();
    // velocity=sum.norma();
    // position += sum;
    // //debugPrint("Direction : x = %Lf, y = %Lf, z = %Lf\n",direction.x,direction.y,direction.z);

}

void Object::applyGravityPull(Object* obj){
    gravity.insert(obj);
}
void Object::removeGravityPull(Object* obj){
    gravity.erase(obj);
}

Vector Object::calcGravitationalForce(Object* obj1,Object* obj2){
    Point a = obj1->getPosition();
    Point b = obj2->getPosition();
    float dist = a.distance(b);
    if(dist==0){
        return Vector(0,0,0);
    }
    long double str = ((long double)(G*obj1->getMass()*obj2->getMass())/(long double)(dist*dist));
    //printf("Gravitic strength: %Lf\n",str);
    Vector vec(a,b);
    Vector vec_final = vec.unitVector();
    return vec_final*str;

}

void Object::setForceToOrbit(Object* center, float angle){
    Point centerPos = center->getPosition();
    Point a_pos = position;
    direction = getOrbitalDirection(centerPos,a_pos,angle);
    velocity = getOrbitalNeededVelocity(center->getMass(),centerPos.distance(a_pos))*2.5;
}