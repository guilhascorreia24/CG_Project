#include "BaseNave.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint BaseNave::width=0;
GLint BaseNave::height=0;
unsigned int BaseNave::texture=0;

//GLboolean separado;

void BaseNave::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/base_nave.jpg", &width, &height, &n, 0);
    printf("base %d %d\n",width,height);

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

BaseNave::BaseNave(Point &center):center(center){
    separado=true;
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/base_nave.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

BaseNave::~BaseNave(){
    glDeleteBuffers(1,&pattern_buffer);
}

void BaseNave::drawShape(){
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

void BaseNave::Update(){
    
}

const char* BaseNave::getLabel(){
    if(separado==true)
        return "Disco da Nave";
    else{
        return "Nave";
    }
}
