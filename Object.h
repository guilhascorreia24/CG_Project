#pragma once
#include "utils.h"


class Object{
    public:
        Object();
        Object(Point & pos, AngleRotation & rotation, Vector & direction, float velocity);
        virtual ~Object();


        void draw();
        void rotate(AngleRotation &rot);
        inline void setRotation(AngleRotation & rot){this->rot = rot;};
        AngleRotation getRotation();
        Point getPosition();
        inline void setPosition(Point & point){this->position = point;}

        inline void setVelocity(float vel){velocity = vel;}
        inline float getVelocity(){return velocity;}

        inline Vector getDirection(){return direction;};
        inline void setDirection(Vector & direction){this->direction = direction.unitVector();};

        void update();
        
    protected:
        void virtual drawShape() = 0;
        void virtual Update() = 0;
        virtual const char* getLabel() = 0;

    protected:
        Point position;
    
    protected:
        AngleRotation rot;
        float velocity;
        Vector direction;

    public:
        static bool drawLabels; 
};

