#pragma once
#include "Object.h"
#include "stb_image.h"

class Nave : public Object{
    public:
        Nave();
        ~Nave();
        static  void inicializarTextura();
        //static unsigned int texture;
    protected:
        void drawShape();
        void Update();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
        std::vector<glm::vec2> uv;
        std::vector< glm::vec3 > normals;
        std::vector< arr > f;
        static GLint width, height;
        static unsigned int texture; 
};