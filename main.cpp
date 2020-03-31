/*
Em linux, para compilar:
$ gcc -o letraH letraH.c -lGL -lGLU -lglut -lm


*/
#include "World.h"
#include "RotationHandler.h"
#include "utils.h"

#define PI 3.14159
static GLfloat spin = 0.0;
int i;

Object* cube;
World* world;
RotationHandler* rot;

void init(void)
{
    cube = new Cube();
    world = new World(cube);
    rot = new RotationHandler(world);
    rot->Start();
    
    glClearColor (0.0, 0.0, 1.0, 0.0);
    glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);
/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

    glPushMatrix();
/*    glTranslatef(-10.0,-10.0,0.0);  */
    glLoadIdentity();
/*    glRotatef(spin, 0.0, 1.0, 0.0); */
    glScalef(3.0, 3.0, 3.0);

    glColor3f (1.0, 0.0, 0.0);
    cube->draw();


    glPopMatrix();
    glutSwapBuffers();

}

void spinDisplay(void)
{
    spin=spin+0.1;
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
    switch (button) {
      case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN)
	  glutIdleFunc(spinDisplay);
        break;
      case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN)
	  glutIdleFunc(NULL);
        break;
      default:
        break;
      }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(250, 250);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    //glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
