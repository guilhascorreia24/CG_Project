#include "GL/glut.h"


struct AngleRotation{
    float x,y,z;
    float angle;
};

class Object{
    public:
        void draw();
        void setRotation(AngleRotation &rot);
    protected:
        void virtual drawShape() = 0;
    private:
        AngleRotation rot;
};