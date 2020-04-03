#include "Camera.h"

Camera::Camera(){
}

Camera::~Camera(){
	printf("NOp\n");
	Stop();
}

void Camera::Start(){
	start = true;
}
void Camera::Stop(){
	start = false;
}
void Camera::keyboardCamera(int key, int x, int y){
	if(!start){
		return;
	}
	switch(key){
		case GLUT_KEY_F1:
		     glLoadIdentity();
			camera1();
			camara=1;
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F2:
		     glLoadIdentity();
			camera2();
			camara=2;
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F3:
		     glLoadIdentity();
			camera3();
			camara=3;
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F4:
		     glLoadIdentity();
			camera4();
			camara=4;
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F5:
		     glLoadIdentity();
			camera5();
			camara=5;
			    glutPostRedisplay();
			break;
		case GLUT_KEY_F6:
		     glLoadIdentity();
			camera6();
			camara=6;
			    glutPostRedisplay();
			break;
		default:
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
