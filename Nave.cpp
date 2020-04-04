#include "Nave.h"
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
GLint Nave::width=0;
GLint Nave::height=0;
unsigned int Nave::texture=0;


void Nave::inicializarTextura(){

    int n;
    //int width,height;
    unsigned char *dados = stbi_load("preto.jpg", &width, &height, &n, 0);
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

Nave::Nave(){
    pattern_buffer = 0; 
    glGenBuffers(1, &pattern_buffer);	
	glBindBuffer(GL_ARRAY_BUFFER, pattern_buffer);		

    bool res = loadObj("objs/nave.obj", &points, &uv,&normals,&f);

  
    glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(glm::vec3), points.data(), GL_STATIC_DRAW);
    if(!res){
        throw std::runtime_error("Error loading object");
    }
}

Nave::~Nave(){
    glDeleteBuffers(1,&pattern_buffer);
}

void Nave::drawShape(){
    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_TRIANGLES);


    

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


    for (int i = 0; i < points.size(); i++)
    {
        glTexCoord2f(uv[i].x, -uv[i].y );
        //3f(points[i].x/width, points[i].y/height, points[i].z); 
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        glVertex3f(points[i].x, points[i].y, points[i].z); 
    }


    // for(glm::vec3 point : points){
    //     //glTexCoord3d(point.x,point.y,point.z);
    //     //glTexCoord2f(model->vt[model->vt_i[i][j] - 1][0], -model->vt[model->vt_i[i][j] - 1][1]);
    //     //glNormal3f(model->vn[model->vn_i[i][j] - 1][0], model->vn[model->vn_i[i][j] - 1][1], model->vn[model->vn_i[i][j] - 1][2]);
    //     //glVertex3f(point.x,point.y,point.z);

    //     //glTexCoord3d(point.x,point.y,point.z);
    //    // glVertex3f(point.x,point.y,point.z);
    //     glVertex3f(point.x,point.y,point.z);
    // }
    glEnd();
    glDisable(GL_TEXTURE_2D);  


    //glDrawArrays(GL_TRIANGLES, 0, points.size());
   // glDisableClientState(GL_VERTEX_ARRAY);
   // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Nave::Update(){
    
}