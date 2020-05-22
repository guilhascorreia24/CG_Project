#include "Sol.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Sol::width=0;
GLint Sol::height=0;
unsigned int Sol::texture=0;



void Sol::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/sol.jpg", &width, &height, &n, 0);

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

Sol::Sol(Point &center):center(center){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/sol.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Sol::~Sol(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Sol::setSizeObject(){
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

void Sol::drawShape(){
    GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f}; 
    glMaterialfv(GL_FRONT, GL_EMISSION, white);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 128);
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
    GLfloat def[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat def1[] = {0.2f, 0.2f, 0.2f, 1.0f}; 
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, def1);
    glMaterialfv(GL_FRONT, GL_EMISSION, def);
    glMaterialfv(GL_FRONT, GL_SPECULAR, def);
    glMaterialf(GL_FRONT, GL_SHININESS, 30);
}

void Sol::Update(){
    
}

const char* Sol::getLabel(){
    return "Sol";
}
