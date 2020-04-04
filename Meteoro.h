#pragma once
#include "Object.h"
#include "stb_image.h"

class Meteoro : public Object{
    public:
        Meteoro(Point &center);
        ~Meteoro();
        static  void inicializarTextura();

    protected:
        void drawShape();
        void Update();
        const char* getLabel();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
        static GLint width, height;
        Point center;
};