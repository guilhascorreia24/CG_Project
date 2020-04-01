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
		     glLoadIdentity();
			camera1();
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F2:
		     glLoadIdentity();
			camera2();
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F3:
		     glLoadIdentity();
			camera3();
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F4:
		     glLoadIdentity();
			camera4();
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F5:
		     glLoadIdentity();
			camera5();
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F6:
		     glLoadIdentity();
			camera6();
			    glutPostRedisplay();
			break;		
	}
}
void Camera::camera1(){
	gluLookAt(50,0,0,0,0,0,0,1,0);
}
void Camera::camera2(){
	gluLookAt(-50,0,0,0,0,0,0,1,0);
}
void Camera::camera3(){
	gluLookAt(0,50,0,0,0,0,1,0,0);
}
void Camera::camera4(){
	gluLookAt(0,-50,0,0,0,0,1,0,0);
}
void Camera::camera5(){
		gluLookAt(0,0,50,0,0,0,1,0,0);
}
void Camera::camera6(){
		gluLookAt(0,0,-50,0,0,0,1,0,0);
}
