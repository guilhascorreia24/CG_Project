#pragma once
#include "Object.h"
#include "stb_image.h"

class BaseNave : public Object{
    public:
        BaseNave();
        ~BaseNave();
        static void inicializarTextura();

    protected:
        void drawShape();
        void Update();
        const char* getLabel();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
        std::vector<glm::vec2> uv;
        std::vector< glm::vec3 > normals;
        std::vector< arr > f;
        static GLint width, height;
        static unsigned int texture; 
        //GLboolean separado;
};