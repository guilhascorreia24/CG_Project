#pragma once
#include "Object.h"
#include "stb_image.h"

class Meteoro : public Object{
    public:
        Meteoro();
        ~Meteoro();
        static  void inicializarTextura();

    protected:
        void drawShape();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
        static GLint width, height;
};