#pragma once
#ifdef _WIN32
#include <gl/glut.h>
#endif
#ifdef unix
#include <stdbool.h>
#include "GL/glut.h"
#define TRUE true
#define FALSE false
#endif

#include <math.h>


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

    inline void operator+=(AngleRotation* a){
        setXRotation(x+= a->x);
        setYRotation(y+= a->y);
        setZRotation(z+= a->z);
    }
    inline void operator-=(AngleRotation* a){
        setXRotation(x-= a->x);
        setYRotation(y-= a->y);
        setZRotation(z-= a->z);
    }

    float x,y,z;
};


struct Point{
    Point(float x, float y, float z) : x(x) , y(y) , z(z){}
    float x,y,z;
};