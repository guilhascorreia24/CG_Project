#include "BaseNave.h"
#include "math.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint BaseNave::width=0;
GLint BaseNave::height=0;
unsigned int BaseNave::texture=0;

void BaseNave::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/base_nave.jpg", &width, &height, &n, 0);
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

BaseNave::BaseNave(Point &center,Point & pos_incial):center(center),pos_incial(pos_incial){
    separado=true;
    colidiu=false;
    pattern_buffer = 0; 
    this->pos_incial=pos_incial;
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


void BaseNave::setSizeObject(){
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
    if(separado==true){
        if(position.x!=center.x) 
            position.x -= position.x*velocity;
        if(position.y!=center.y) 
            position.y -= position.y*velocity;
        if(position.z!=center.z) 
            position.z -= position.z*velocity;
        if(position == center){
            separado=false;
            printf("Nave pode ser Movida\n");
            comecou = true;
        } 

    }else if(colidiu == true){
        position.x += position.x*velocity;
        
        position.y += position.y*velocity;

        position.z += position.z*velocity;
        if(position.x>=center.x){
            colidiu = false;
        }
    }
}

const char* BaseNave::getLabel(){
    if(separado==true)
        return "Disco da Nave";
    else{
        return "Nave";
    }
}
