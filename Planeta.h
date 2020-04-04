#pragma once
#include "Object.h"
#include "stb_image.h"

class Planeta : public Object{
    public:
        Planeta(Point &center);
        ~Planeta();
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