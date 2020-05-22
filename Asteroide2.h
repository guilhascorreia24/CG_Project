#pragma once
#include "Object.h"
#include "stb_image.h"

class Asteroide2 : public Object{
    public:
        Asteroide2(Point &center);
        ~Asteroide2();
        static void inicializarTextura();
        void setSizeObject();
        bool canMove(){return true;}

    protected:
        void drawShape();
        void Update();
        const char* getLabel();

    private:
        Point center;
        GLuint pattern_buffer;
        std::vector<glm::vec2> uv;
        std::vector< glm::vec3 > normals;
        std::vector< arr > f;
        static GLint width, height;
        static unsigned int texture; 
};