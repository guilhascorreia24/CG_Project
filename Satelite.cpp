#include "Satelite.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Satelite::width=0;
GLint Satelite::height=0;
unsigned int Satelite::texture=0;


void Satelite::inicializarTextura(){

    int n;
    //int width,height;
    unsigned char *dados = stbi_load("img/metal.jpg", &width, &height, &n, 0);
    printf("%d %d\n",width,height);

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
Satelite::Satelite(Point &center):center(center){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/satelite.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Satelite::~Satelite(){
    glDeleteBuffers(1,&pattern_buffer);
}



void Satelite::setSizeObject(){
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
    this->min.x = min_x;
    this->min.y = min_y;
    this->min.z = min_z;
    this->max.x = max_x;
    this->max.y = max_y;
    this->max.z = max_z;
}



void Satelite::drawShape(){
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


const char* Satelite::getLabel(){
    return "Satelite";
}

void Satelite::Update(){
    /*printf("Satelite Position->");
    position.print();
    printf("Satelite Velocity-> %Lf\n",velocity);
    printf("Satelite Direction->");
    direction.print();
    auto it = gravity.begin();
    Point obj = (*it)->getPosition();
    printf("Distance to Sun-> %lf\n",obj.distance(position));*/

}