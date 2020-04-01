#include "Camera.h"

Camera::Camera(){
}

Camera::~Camera(){
	printf("NOp\n");
	Stop();
}

void Camera::Start(){
	glutSpecialFunc(keyboardCamera);
}
void Camera::Stop(){
	glutSpecialFunc(NULL);
}
void Camera::keyboardCamera(int key, int x, int y){
	switch(key){
		case GLUT_KEY_F1:
			camera1();
			printf("entrei\n");
			break;
		case GLUT_KEY_F2:
			camera2();
			break;
		case GLUT_KEY_F3:
			camera3();
			break;
		case GLUT_KEY_F4:
			camera4();
			break;
		case GLUT_KEY_F5:
			camera5();
			break;
		case GLUT_KEY_F6:
			camera6();
			break;		
	}
	    glutPostRedisplay();
}
void prespective(){
		// Especifica sistema de coordenadas de projeçã

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
}
void Camera::camera1(){
	prespective();
	gluLookAt(50,0,0,0,0,0,0,1,0);
}
void Camera::camera2(){
	gluLookAt(-50,0,0,0,0,0,0,1,0);
}
void Camera::camera3(){
		prespective();
	gluLookAt(0,50,0,0,0,0,1,0,0);
}
void Camera::camera4(){
		prespective();
	gluLookAt(0,-50,0,0,0,0,1,0,0);
}
void Camera::camera5(){
		prespective();
		gluLookAt(0,0,50,0,0,0,1,0,0);
}
void Camera::camera6(){
		gluLookAt(0,0,-50,0,0,0,1,0,0);
}
