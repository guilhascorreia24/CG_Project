#include "Nave.h"
#include <stdexcept>


Nave::Nave(){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    std::vector< glm::vec2 > uv; // Won't be used at the moment.
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    bool res = loadObj("objs/nave.obj", &points, &uv,&normals);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Nave::~Nave(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Nave::drawShape(){
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, points.size());
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}