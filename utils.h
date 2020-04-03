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

#define PRINT_ERRORS TRUE
#define PRINT_DEBUG TRUE


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
    Vector(float x, float y, float z);

    inline Vector operator*(float _const){
        return Vector(x*_const,y*_const,z*_const);
    }

    inline void operator+=(Vector& a){
        x+= a.x;
        y+= a.y;
        z+= a.z;
    }
    inline void operator-=(Vector& a){
        x-= a.x;
        y-= a.y;
        z-= a.z;
    }

    float x,y,z;
};


void debugPrint(const char* format, ...);

void errorPrint(const char* format, ...);


struct Point{
    Point(float x, float y, float z) : x(x) , y(y) , z(z){}

    inline void operator+=(Vector & a){
        x+= a.x;
        y+= a.y;
        z+= a.z;
    }
    
    float x,y,z;
};
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
bool loadObj(const char* filename, std::vector<glm::vec3>* vertices,std::vector<glm::vec2>* uvs,std::vector<glm::vec3>* normals);

int getFileSize(FILE * file);