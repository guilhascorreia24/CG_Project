#pragma once
#include "utils.h"


class Object{
    public:
        Object();
        virtual ~Object();
        void draw();
        void rotate(AngleRotation &rot);
        AngleRotation getRotation();
    protected:
        void virtual drawShape() = 0;
    private:
        AngleRotation rot;
};

