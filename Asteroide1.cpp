#include "Asteroide1.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Asteroide1::width=0;
GLint Asteroide1::height=0;
unsigned int Asteroide1::texture=0;



void Asteroide1::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/asteroide1.jpg", &width, &height, &n, 0);
    printf("asteroide1 %d %d\n",width,height);

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

Asteroide1::Asteroide1(Point &center):center(center){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/asteroide1.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Asteroide1::~Asteroide1(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Asteroide1::drawShape(){
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);
  
    for (int i = 0; i < (int)points.size(); i++)
    {

        glTexCoord2f(uv[i].x, uv[i].y);
        
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        
        glVertex3f(points[i].x, points[i].y, points[i].z); 
    }

    glEnd();
    glDisable(GL_TEXTURE_2D);  
}

void Asteroide1::Update(){
    
}

const char* Asteroide1::getLabel(){
    return "Asteroide";
}
