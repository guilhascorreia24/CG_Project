#include "Foguetao.h"
#include "math.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Foguetao::width=0;
GLint Foguetao::height=0;
unsigned int Foguetao::texture=0;


void Foguetao::inicializarTextura(){

    int n;
    unsigned char *dados = stbi_load("img/foguetao.jpg", &width, &height, &n, 0);
    printf("missil %d %d\n",width,height);

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

Foguetao::Foguetao(Point &center):center(center){
    limite_alcancado=false;
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/foguetao.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Foguetao::~Foguetao(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Foguetao::drawShape(){
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

void Foguetao::Update(){
    if(limite_alcancado == false){
        static long time = glutGet(GLUT_ELAPSED_TIME);
        long time_elapsed = glutGet(GLUT_ELAPSED_TIME) - time;
        position.x -= velocity;
        position.z -= velocity*0.5;
        if(position.x < 0)
            limite_alcancado = true;
    }else{
        position.x=center.x;
        position.y=center.y;
        position.z=center.z;
        limite_alcancado = false;
    }
}

const char* Foguetao::getLabel(){
    return "Foguetao";
}
