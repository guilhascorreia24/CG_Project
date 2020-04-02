#pragma once
#include "utils.h"


class Object{
    public:
        Object();
        Object(Point & pos);
        virtual ~Object();
        void draw();
        void rotate(AngleRotation &rot);
        AngleRotation getRotation();
        Point getPosition();
        void setPosition(Point & point);
        
    protected:
        void virtual drawShape() = 0;
    protected:
        AngleRotation rot;
        Point position;

};

