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

#define PI 3.14159
static GLfloat spin = 0.0;
int i;

Object* nave;
World* world;
RotationHandler* rot;
Object* nave_sem_perna;
World* world1;
RotationHandler* rot1;
void init(void)
{
    nave = new Nave();
    nave_sem_perna=new nave_sem_pernas();
    world = new World(nave);
    world1=new World(nave_sem_perna);
    rot = new RotationHandler(world);
    rot1 = new RotationHandler(world1);
    rot->Start();
    rot1->Start();
    
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

    glPushMatrix();
/*    glTranslatef(-10.0,-10.0,0.0);  */
    glLoadIdentity();
    glRotatef(spin, 0.0, 1.0, 0.0); 
    glScalef(3.0, 3.0, 3.0);

    glColor3f (1.0, 1.0, 0.0);
    nave->draw();
    nave_sem_perna->draw();


    glPopMatrix();
    glutSwapBuffers();

}

void spinDisplay(void)
{
    spin=spin+2;
    if (spin > 360.0)
        spin=spin-360.0; 
    glutPostRedisplay();
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

void mouse(int button, int state, int x, int y)
{
    rot->keyboardHandler(button,x,y);
}

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
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
