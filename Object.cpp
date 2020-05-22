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
    return tmp;
}

Point Object::getPosition(){
    return position;
}
Object::Object() : position(0,0,0),size_object(0,0,0),min(0,0,0),max(0,0,0),rot(0,0,0),velocity(0),direction(0,0,0),mass(1),thisCenter(0,0,0){
    size = 1;
    last_update_time = glutGet(GLUT_ELAPSED_TIME);
    lastAngle = 0;
    lastRadius = 0;
    thisCenter = Vector(0,0,0);
    e = 0;
    useVelocityGravityPhisics = true;
    useUniformOrbit = false;
    perdeu = false;
}
Object::~Object(){
}

Object::Object(Point & pos, Point & size_obj,Point & min, Point & max,AngleRotation & rotation, Vector & direction, long double velocity, long double mass) : mass(mass),position(pos),size_object(size_obj),min(min), max(max),rot(rotation) ,velocity(velocity),direction(direction),thisCenter(0,0,0){
    size = 1;
    last_update_time = glutGet(GLUT_ELAPSED_TIME);
    lastAngle = 0;
    lastRadius = 0;
    e = 0;
    useVelocityGravityPhisics = true;
    useUniformOrbit = false;
    comecou = false;
}


void Object::update(){
    Update();
    //long currTime = glutGet(GLUT_ELAPSED_TIME);
    //double time_elapsed = ((double)(currTime-last_update_time))/1000.f;

    //Calculate new position according to direction and velocity
    if(useVelocityGravityPhisics){
        Vector sum(0,0,0);
        for(Object* a: gravity){
            Vector b = calcGravitationalForce(this,a);
            sum+= b;
        }
    

        //Momentum
        Vector vec = direction*velocity;

        sum+=vec;
        direction=sum.unitVector();
        velocity=sum.norma();
        //sum*=time_elapsed;
        position += sum;
        //debugPrint("Direction : x = %Lf, y = %Lf, z = %Lf\n",direction.x,direction.y,direction.z);
        //last_update_time = currTime;
    }

    //Next position to orbit
    if(useUniformOrbit){
        Point sunPos = orbit->getPosition();
        Point thisCenter = sunPos;
        thisCenter+=this->thisCenter;
        double a = thisCenter.distance(sunPos)*2;
        double b = a * sqrt(-(e*e-1));
        lastAngle+=velocity/lastRadius;
        double cosO = cos(lastAngle);
        double sinO = sin(lastAngle);
        double param2 = 0;
        if(sinO == 0){
            param2==0;
        }else{
            param2 = (b*b)/sinO*sinO;
        }
        double radius = sqrt(((a*a)/cosO*cosO)+param2);
        double x = thisCenter.x + radius*cosO;
        double z = thisCenter.z + radius*sinO;
        lastRadius = radius;

        position.x = x;
        position.z = z;
    }

}

void Object::applyGravityPull(Object* obj){
    useVelocityGravityPhisics = true;
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
    Vector vec(a,b);
    Vector vec_final = vec.unitVector();
    return vec_final*str;

}

void Object::setForceToOrbit(Object* center, float angle, float e){
    useVelocityGravityPhisics = true;
    Point centerPos = center->getPosition();
    Point a_pos = position;
    direction = getOrbitalDirection(centerPos,a_pos,angle);
    velocity = e*(getOrbitalNeededVelocity(center->getMass(),centerPos.distance(a_pos))*60);
}

void Object::setUniformOrbit(Object *sun, double e, double velocity){
    useUniformOrbit = true;
    useVelocityGravityPhisics = false;
    if(velocity!=0)
        this->velocity = velocity; 
    orbit = sun;
    Point a = sun->getPosition();
    thisCenter = Vector(position,a);
    lastRadius = sun->getPosition().distance(position);

    this->e = e;    
}

std::vector<glm::vec3> Object::getPoints(){
    return this->points;
}