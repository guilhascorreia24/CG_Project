#include "World.h"
#include "Camera.h"
#include "RotationHandler.h"
#include "Camera.h"
#include "utils.h"
#include "Nave.h"
#include "nave_sem_pernas.h"
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define PI 3.14159
//static GLfloat spin = 0.0;
int i;
bool pressed=false;
GLfloat angle, fAspect;
World* world;
RotationHandler* rot;
Camera* cam;
GLint Window;
GLfloat win;


bool iluminacao,shading=true,antialiasing=true;



void keyboardHandler(int key,int x, int y){
    rot->keyboardHandler(key,x,y);
    cam->keyboardCamera(key,x,y);
}

void teclas(unsigned char key, int x,int y){
    switch (key)
    {
    case 'w':
     glLoadIdentity();
        if(!pressed){pressed=true;}
        else{pressed=false;} 
        glLoadIdentity();
        break;      
    case 'a':
     rot->keyboardSpeed(key, x, y);
     break;
    case 'z':
        rot->keyboardSpeed(key,x,y);
        break;
    case 27:
        glutDestroyWindow(Window);
        exit(0);
        break;
    case '+':
        win -= 1;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           glOrtho(-win, win, -win, win, -win*2, win*2);
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
           
            if(cam->camara==1)
	           gluLookAt(50,0,0,0,0,0,0,1,0);
            else if(cam->camara==2)
	           gluLookAt(-50,0,0,0,0,0,0,1,0);
            else if(cam->camara==3)
	            gluLookAt(0,50,0,0,0,0,1,0,0);
            else if(cam->camara==4)
	            gluLookAt(0,-50,0,0,0,0,1,0,0);
            else if(cam->camara==5)
		        gluLookAt(0,0,50,0,0,0,1,0,0);
            else if(cam->camara==6)
		        gluLookAt(0,0,-50,0,0,0,1,0,0);

        break;

    case '-':
            win += 1;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           glOrtho(-win, win, -win, win, -win*2, win*2);
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
           

            if(cam->camara==1)
	           gluLookAt(50,0,0,0,0,0,0,1,0);
            else if(cam->camara==2)
	           gluLookAt(-50,0,0,0,0,0,0,1,0);
            else if(cam->camara==3)
	            gluLookAt(0,50,0,0,0,0,1,0,0);
            else if(cam->camara==4)
	            gluLookAt(0,-50,0,0,0,0,1,0,0);
            else if(cam->camara==5)
		        gluLookAt(0,0,50,0,0,0,1,0,0);
            else if(cam->camara==6)
		        gluLookAt(0,0,-50,0,0,0,1,0,0);
        break; 
    }
    glutPostRedisplay();
}

void display(void)
{
    
    
    // if(iluminacao==true){    
    //     luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
    // }
    // else{
    //    luzAmbiente[4]={0.0,0.0,0.0,0.0}; 
    // }

    // if (shading==true)
    //     glShadeModel (GL_FLAT);
    // else
    //     glShadeModel(GL_SMOOTH);
    

    if (antialiasing==true){
        glEnable(GL_BLEND);
        glDisable(GL_DEPTH_TEST);
        glEnable(GLUT_MULTISAMPLE);
         glEnable(GL_MULTISAMPLE);
    }
    else{
        //glDisable(GL_BLEND);
        //glEnable(GL_DEPTH_TEST);
        glDisable(GL_MULTISAMPLE);
    }
         
    

    //glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

/*    glTranslatef(-10.0,-10.0,0.0);  */
    //gluLookAt(0,0,100,0,0,0,0,0,0);
    glScalef(3.0, 3.0, 3.0);
    glColor3f (1.0, 1.0, 0.0);
    if(pressed){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    world->draw();
    //nave_sem_perna->draw();

    glPopMatrix();
    glutSwapBuffers();
    //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 

}


void init(void)
{
    win=50;


    
    GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};


    // Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 120;


    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);


    // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);





    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);


    //Nave::inicializarTextura();

    world = new World(new Nave());
    rot = new RotationHandler(world);
    cam= new Camera();
    rot->Start();
    cam->Start();

    glutSpecialFunc(keyboardHandler);
	glutKeyboardFunc(teclas);
	
    
    //glClearColor (0.0, 0.0, 1.0, 0.0);
    //glShadeModel (GL_FLAT);
    //glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-win, win, -win, win, -win*2, win*2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Função usada para especificar o volume de visualização
/*void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(45,fAspect,0.4,500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(0,0,50, 0,0,0, 0,1,0);
}*/

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    //EspecificaParametrosVisualizacao();
}

void destroy(){
    delete rot;
    delete cam;
    delete world;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(350, 300);
    glutInitWindowPosition(100, 100);
    Window=glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glewInit();
 
    

    init();
    glutMainLoop();
    destroy();
    return 0;
}


