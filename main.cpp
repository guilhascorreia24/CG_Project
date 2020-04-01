/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm


*/
#include "World.h"
#include "RotationHandler.h"
#include "Camera.h"
#include "utils.h"
#include "Nave.h"
#include "nave_sem_pernas.h"
#include "RotationHandler.h"

#define PI 3.14159
static GLfloat spin = 0.0;
int i;
GLfloat angle, fAspect;
Object* nave;
World* world;
RotationHandler* rot;
Camera* cam;
void init(void)
{
    nave = new Nave();
    world = new World(nave);
    rot = new RotationHandler(world);
    cam= new Camera();
    rot->Start();
    cam->Start();

    
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

/*    glTranslatef(-10.0,-10.0,0.0);  */
    //gluLookAt(0,0,100,0,0,0,0,0,0);
    glRotatef(spin, 0.0, 1.0, 0.0); 
    glScalef(3.0, 3.0, 3.0);

    glColor3f (1.0, 1.0, 0.0);
    nave->draw();
    //nave_sem_perna->draw();


    glutSwapBuffers();

}

void spinDisplay(void)
{
    spin=spin+2;
    if (spin > 360.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}

/*void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-50.0, 50.0, -50.0, 50.0, -100.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}*/

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
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
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}


void keypressed(int button, int x, int y)
{
    rot->keyboardHandler(button,x,y);
    cam->keyboardCamera(button,x,y);
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutSpecialFunc(keypressed);
    glewInit();
    init();
    glutMainLoop();
    return 0;
}
