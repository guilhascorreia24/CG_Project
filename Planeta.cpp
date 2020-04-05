#include "Planeta.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Planeta::width=0;
GLint Planeta::height=0;
unsigned int Planeta::texture=0;



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

    bool res = loadObj("objs/planeta.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Planeta::~Planeta(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Planeta::drawShape(){
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);

    //glColor3f(1.0,1.0,0.0);
    

    // glEnableClientState(GL_VERTEX_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);
    // glVertexPointer(3, GL_FLOAT, 0, 0);


    GLfloat Ka[4]={0.8, 0.8, 0.8, 0.8};
    GLfloat Ns = 500;
    GLfloat Kd[4]={0.8, 0.8, 0.8, 0.8};
    GLfloat Ks[4]={0.8, 0.8, 0.8, 0.8};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Ks);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, Ns);

  
    for (int i = 0; i < (int)points.size(); i++)
    {

        glTexCoord2f(uv[i].x, uv[i].y);
        //3f(points[i].x/width, points[i].y/height, points[i].z); 
        
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        
       // glTextCoord3f(points[i].x/width, points[i].y, points[i].z); 
        
        glVertex3f(points[i].x, points[i].y, points[i].z); 
    }


    
 

    glEnd();
    glDisable(GL_TEXTURE_2D);  


    //glDrawArrays(GL_TRIANGLES, 0, points.size());
   // glDisableClientState(GL_VERTEX_ARRAY);
   // glBindBuffer(GL_ARRAY_BUFFER, 0);
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