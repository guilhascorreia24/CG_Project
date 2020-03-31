#pragma once
#include "Object.h"


class Nave : public Object{
    public:
        Nave();
        ~Nave();

    protected:
        void drawShape();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
};