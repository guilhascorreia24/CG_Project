#include "Asteroide2.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Asteroide2::width=0;
GLint Asteroide2::height=0;
unsigned int Asteroide2::texture=0;



void Asteroide2::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/asteroide2.jpg", &width, &height, &n, 0);
    printf("asteroide 2 %d %d\n",width,height);

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

Asteroide2::Asteroide2(Point &center):center(center){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/asteroide2.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Asteroide2::~Asteroide2(){
    glDeleteBuffers(1,&pattern_buffer);
}
void Asteroide2::setSizeObject(){
    int max_x = -1,min_x = 1000 ,max_y = -1,min_y = 1000 ,max_z = -1,min_z = 1000 ;
    for (int i = 0; i < (int)points.size(); i++)
    {
        if(points[i].x>max_x)
            max_x = points[i].x;
        if(points[i].x<min_x)
            min_x = points[i].x; 
        
        if(points[i].y>max_y)
            max_y = points[i].y;
        if(points[i].x<min_y)
            min_y = points[i].y;  

        if(points[i].z>max_z)
            max_z = points[i].z;
        if(points[i].z<min_z)
            min_z = points[i].z;       
    }
    this->min.x = min_x*size;
    this->min.y = min_y*size;
    this->min.z = min_z*size;
    this->max.x = max_x*size;
    this->max.y = max_y*size;
    this->max.z = max_z*size;
    this->size_object.x=abs(min_x-max_x)*size;
    this->size_object.y=abs(min_y-max_y)*size;
    this->size_object.z=abs(min_z-max_z)*size;
}
void Asteroide2::drawShape(){
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

void Asteroide2::Update(){
}

const char* Asteroide2::getLabel(){
    return "Asteroide";
}
