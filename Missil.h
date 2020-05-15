#pragma once
#include "Object.h"
#include "stb_image.h"

class Missil : public Object{
    public:
        Missil(Point &center);
        ~Missil();
        static  void inicializarTextura();
    protected:
        void drawShape();
        void Update();
        const char* getLabel();

    private:
        Point center;
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
        std::vector<glm::vec2> uv;
        std::vector< glm::vec3 > normals;
        std::vector< arr > f;
        static GLint width, height;
        static unsigned int texture; 
};