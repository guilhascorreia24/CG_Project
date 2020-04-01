/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm


*/
#include "World.h"
#include "RotationHandler.h"
#include "utils.h"
#include "Nave.h"
#include "nave_sem_pernas.h"
#include "RotationHandler.h"
#include "Camera.h"

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
    cam=new Camera();
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
    glLoadIdentity();
    glRotatef(spin, 0.0, 1.0, 0.0); 
    glScalef(3.0, 3.0, 3.0);

    glColor3f (1.0, 1.0, 0.0);
    nave->draw();


    glutSwapBuffers();

}

void spinDisplay(void)
{
    spin=spin+2;
    if (spin > 360.0)
        spin=spin-360.0; 
    glutPostRedisplay();
}

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
    gluLookAt(0,80,200, 0,0,0, 0,1,0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void reshape(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    EspecificaParametrosVisualizacao();
}

void mouse(unsigned char key, int x, int y)
{
    rot->keyboardHandler(key,x,y);
    cam->keyboardCamera(key,x,y);
        EspecificaParametrosVisualizacao();
    glutPostRedisplay();
}
/*
void MoverLetra(int x, int y)
{

    if (moving)
    {
        glutIdleFunc(SemRotacao);
        GLdouble model[16];
        GLdouble proj[16];
        GLint m_viewport[4];

        glGetDoublev(GL_MODELVIEW_MATRIX, model);
        glGetDoublev(GL_PROJECTION_MATRIX, proj);
        glGetIntegerv(GL_VIEWPORT, m_viewport);

        GLdouble rx;
        GLdouble ry;
        GLdouble rz;
        gluUnProject(x, y, 0, model, proj, m_viewport, &rx, &ry, &rz);

        px = rx;
        py = -ry;
        printf("x=%d y=%d\n px=%f py=%f\n", x, y, px, py);
        glutPostRedisplay();
    }
}

*/
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glewInit();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(mouse);
    glutMainLoop();
    return 0;
}
