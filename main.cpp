#include "World.h"
#include "Camera.h"
#include "RotationHandler.h"
#include "Camera.h"
#include "utils.h"
#include "Nave.h"
#include "nave_sem_pernas.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


#define PI 3.14159
//static GLfloat spin = 0.0;
int i;
GLfloat angle, fAspect;
World* world;
RotationHandler* rot;
Camera* cam;


void keyboardHandler(int key,int x, int y){
    rot->keyboardHandler(key,x,y);
    cam->keyboardCamera(key,x,y);
}

void init(void)
{
    Nave::inicializarTextura();
    //nave = new Nave();
    world = new World(new Nave());
    rot = new RotationHandler(world);
    cam= new Camera();
    rot->Start();
    cam->Start();

    glutSpecialFunc(keyboardHandler);

    
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

/*    glTranslatef(-10.0,-10.0,0.0);  */
    //gluLookAt(0,0,100,0,0,0,0,0,0);
    glScalef(3.0, 3.0, 3.0);
    glColor3f (1.0, 1.0, 0.0);
    world->draw();
    //nave_sem_perna->draw();


    glutSwapBuffers();
}


void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
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
    glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glewInit();
    init();
    
    glutMainLoop();
    destroy();
    return 0;
}


