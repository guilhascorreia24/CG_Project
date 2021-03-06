#pragma once
#include "Object.h"
#include "stb_image.h"

class BaseNave : public Object{
    public:
        BaseNave(Point &center,Point &pos_incial);
        ~BaseNave();
        static void inicializarTextura();
        void setSizeObject();
        bool canMove(){return !separado;}
    protected:
        void drawShape();
        void Update();
        const char* getLabel();

    private:
        Point center;
        Point pos_incial;
        GLuint pattern_buffer;
        std::vector<glm::vec2> uv;
        std::vector< glm::vec3 > normals;
        std::vector< arr > f;
        static GLint width, height;
        static unsigned int texture; 
};