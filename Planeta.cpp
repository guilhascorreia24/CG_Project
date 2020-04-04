#include "Planeta.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Planeta::width=0;
GLint Planeta::height=0;



void Planeta::inicializarTextura(){
    unsigned int texture;
    int n;
    //int width,height;
    unsigned char *dados = stbi_load("cinza.jpg", &width, &height, &n, 0);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, dados);
    stbi_image_free(dados);

}

Planeta::Planeta(Point &center):center(center){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    std::vector< arr > f;
    std::vector< glm::vec2 > uv; // Won't be used at the moment.
    std::vector< glm::vec3 > normals; // Won't be used at the moment.
    bool res = loadObj("objs/Planeta.obj", &points, &uv,&normals,&f);
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Planeta::~Planeta(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Planeta::drawShape(){
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    
    
    glDrawArrays(GL_TRIANGLES, 0, points.size());
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


const char* Planeta::getLabel(){
    return "Planeta";
}

void Planeta::Update(){
    static Point p(0,0,0);
    //printf("X: %f Y: %f, Z: %f\n",position.x,position.y,position.z);
    //printf("Distance from last frame: %f\n",p.distance(position));
    p=position;
    Vector vec(center,position);

    //Vector result(1,0.5,0);
    //Prependicular plane equation
    //result.z = (vec.x*(result.x - position.x) + vec.y*(result.y - position.y) - vec.z*position.z)/(-vec.z);
    direction = Vector(vec.y,-vec.x,0);
    setDirection(direction);

}