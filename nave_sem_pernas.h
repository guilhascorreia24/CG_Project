#pragma once
#include "Object.h"


class nave_sem_pernas : public Object{
    public:
        nave_sem_pernas();
        ~nave_sem_pernas();

    protected:
        void drawShape();

    private:
        GLuint pattern_buffer;
        std::vector<glm::vec3> points;
};