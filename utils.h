#pragma once
#ifdef _WIN32
#include <gl/glut.h>
#endif
#ifdef unix

#include <GL/glew.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <unistd.h>
#define TRUE true
#define FALSE false

#endif

#include <math.h>
#include <stdio.h>
#include <vector>
#include <stdarg.h> 
#include <string>
#include <cstring>
#include <ctime>

#define PRINT_ERRORS FALSE
#define PRINT_DEBUG FALSE
#define PI 3.14159
#define G 0.0001
#define SPEED 1
#define EPSILON 0.00002

struct Point;
bool equalFloat(float a, float b);
struct AngleRotation{
    AngleRotation(float x_angle, float y_angle, float z_angle);

    float getXRotation(){return x;}
    float getYRotation(){return y;}
    float getZRotation(){return z;}

    void setXRotation(float angle){x= normalizeAngle(angle);}
    void setYRotation(float angle){y= normalizeAngle(angle);}
    void setZRotation(float angle){z= normalizeAngle(angle);}

    inline float normalizeAngle(float angle){
        float _angle = angle;
        if(_angle < 0 || angle> 360.0){
            _angle = fmod(angle,360.0);
        }
        return _angle;
    }

    inline void operator+=(AngleRotation & a){
        setXRotation(x+= a.x);
        setYRotation(y+= a.y);
        setZRotation(z+= a.z);
    }
    inline void operator-=(AngleRotation & a){
        setXRotation(x-= a.x);
        setYRotation(y-= a.y);
        setZRotation(z-= a.z);
    }

    float x,y,z;
};

struct Vector{
    Vector(long double x, long double y, long double z);

    Vector(Point & a, Point & b);

    Vector(Vector* a) : x(a->x),y(a->y),z(a->z){

    }

    inline Vector operator*(long double _const){
        return Vector(x*_const,y*_const,z*_const);
    }

    inline float norma(){
        return sqrt(x*x + y*y +z*z);
    }

    inline Vector unitVector(){
        long double n = norma();
        long double x,y,z;
        if(n==0){
            x=0;
            y=0;
            z=0;
            return Vector(x,y,z);
        }
        x = this->x/n;
        y = this->y/n;
        z = this->z/n;
        return Vector(x,y,z);
    }

    inline void operator+=(Vector& a){
        x+= a.x;
        y+= a.y;
        z+= a.z;
    }
    inline void operator*=(long double _const){
        x*=_const;
        y*=_const;
        z*=_const;
    }

    inline void operator-=(Vector& a){
        x-= a.x;
        y-= a.y;
        z-= a.z;
    }

    inline void print(){
        printf("Vector.x = %Lf, Vector.y = %Lf, Vector.z = %Lf\n",x,y,z);
    }

    long double x,y,z;
};

long double getOrbitalNeededVelocity(long double massCentral, float distance);
Vector getOrbitalDirection(Point a, Point b,float angle);
Vector rotateVector(Vector &vec, Vector &axis,float angle);
Vector crossProduct(Vector &a, Vector &b);
float dotProduct(Vector &a, Vector &b);

void debugPrint(const char* format, ...);

void errorPrint(const char* format, ...);


struct Point{
    Point(float x, float y, float z) : x(x) , y(y) , z(z){}
    Point(Point *a) : x(a->x), y(a->y), z(a->z){} 

    inline void operator+=(Vector & a){
        x+= a.x;
        y+= a.y;
        z+= a.z;
    }

    inline void operator-=(Vector & a){
        x-= a.x;
        y-= a.y;
        z-= a.z;
    }

    inline Point operator+(Vector & a){
        Point b(this);
        b+=a;
        return b;
    }

    inline Point operator-(Vector & a){
        Point b(this);
        b-=a;
        return b;
    }

    inline bool operator==(Point & a){
        return equalFloat(a.x,x) && equalFloat(a.y,y) && equalFloat(a.z,z); 
    }

    inline float distance(Point & a){
         
        return sqrt((a.x-x)*(a.x-x) + (a.y-y)*(a.y-y) + (a.z-z)*(a.z-z));
    }

    inline void print(){
        printf("Point.x = %f, Point.y = %f, Point.z = %f\n",x,y,z);
    }
    
    float x,y,z;
};

struct arr{
    unsigned int f[9];
};
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool loadObj(const char* filename, std::vector<glm::vec3>* vertices,std::vector<glm::vec2>* uvs,std::vector<glm::vec3>* normals,std::vector<arr>* f);

int getFileSize(FILE * file);
inline clock_t getTimeInMili(){return glutGet(GLUT_ELAPSED_TIME);}