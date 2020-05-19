#include "DiscoNave.h"
#include <stdexcept>
#include "math.h"
#define STB_IMAGE_IMPLEMENTATION
GLint DiscoNave::width=0;
GLint DiscoNave::height=0;
unsigned int DiscoNave::texture=0;

void DiscoNave::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/disco_nave.jpg", &width, &height, &n, 0);
    printf("disco %d %d\n",width,height);

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

DiscoNave::DiscoNave(Point &center,Point & pos_incial):center(center),pos_incial(pos_incial){
    separado=true;
    colidiu=false;
    pattern_buffer = 0; 
    this->pos_incial=pos_incial;
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/disco_nave.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

DiscoNave::~DiscoNave(){
    glDeleteBuffers(1,&pattern_buffer);
}

void DiscoNave::setSizeObject(){
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
    this->size_object.x= abs(min_x-max_x);
    this->size_object.y= abs(min_y-max_y);
    this->size_object.z= abs(min_z-max_z);
}

void DiscoNave::drawShape(){
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

void DiscoNave::Update(){
    if(separado==true){
        if(position.x!=center.x) 
            position.x -= position.x*velocity;
        if(position.y!=center.y) 
            position.y -= position.y*velocity;
        if(position.z!=center.z) 
            position.z -= position.z*velocity;
        if(position == center){
            separado=false;
        }
    }else if(colidiu == true){
        if(position.x<pos_incial.x) 
            position.x += position.x*velocity;
        if(position.y<pos_incial.y) 
            position.y += position.y*velocity;
        if(position.z<pos_incial.z) 
            position.z += position.z*velocity;
        if(position == pos_incial){
            colidiu=false;
        }

    }
}

const char* DiscoNave::getLabel(){
    if(separado==true)
        return "Disco da Nave";
    else{
        return "Nave";
    }
}
