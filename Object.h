#pragma once
#include "utils.h"
#include <set>

class Object{
    public:
        Object();
        Object(Point & pos,Point & size_obj,Point & min,Point & max, AngleRotation & rotation, Vector & direction, long double velocity, long double mass);
        virtual ~Object();


        void draw();
        void rotate(AngleRotation &rot);
        void mover(double x,double y, double z);
        inline void setRotation(AngleRotation & rot){this->rot = rot;};
        AngleRotation getRotation();
        Point getPosition();
        inline void setPosition(Point & point){this->position = point;}
        Point getSizeObject();
        // inline void setSizeObject(std::vector<glm::vec3> points);

        inline void setVelocity(long double vel){velocity = vel;}
        inline float getVelocity(){return velocity;}

        inline Vector getDirection(){return direction;};
        inline void setDirection(Vector & direction){this->direction = direction.unitVector();}

        inline void setSize(int num){this->size = num;}
        inline int getSize(){return size;}

        void setMomentum(Vector &a){setDirection(a);setVelocity(a.norma());}

        inline void setMass(long double mass){this->mass = mass;}
        inline long double getMass(){return mass;}

        void setUniformOrbit(Object *planet, double e, double velocity=0);

        /*PHISICS*/
        void disablePhisycs(){useVelocityGravityPhisics=false;}

        //Aply a force with and id
        //oid aplyForce(int id,Vector& force);
        //void deleteForce(int id);

        void applyGravityPull(Object* obj);
        void removeGravityPull(Object* obj);

        //Set the initial velocity needed for orbit
        //variable e represents the eccentrecity
        void setForceToOrbit(Object* obj, float angle, float e);
        static Vector calcGravitationalForce(Object* obj1,Object* obj2);
        
        void update();
        std::vector<glm::vec3> getPoints();

    protected:
        void virtual drawShape() = 0;
        void virtual Update() = 0;
    public:
        bool virtual canMove() = 0;
    public:
        virtual const char* getLabel() = 0;

    
    protected:
        AngleRotation rot;
        long double velocity;
        Vector direction;
        int size;
        Point position;
        Point size_object;
        std::set<Object*> gravity;
        
        //Uniform Orbit
        Object* orbit;
        float lastAngle;
        float lastRadius;
        Point thisCenter;
        double e;
        bool useUniformOrbit;
    private:
        bool useVelocityGravityPhisics;
        long double mass;
        long last_update_time;


    public:
        static bool drawLabels; 
        GLboolean colidiu;
        bool comecou;
        Point min;
        Point max;
        std::vector<glm::vec3> points;
};

