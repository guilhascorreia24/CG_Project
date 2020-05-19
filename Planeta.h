#pragma once
#include "Object.h"
#include "stb_image.h"

class Planeta : public Object{
    public:
        Planeta(Point &center);
        ~Planeta();
        static  void inicializarTextura();
        void setSizeObject();
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