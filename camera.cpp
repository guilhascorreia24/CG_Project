#include "Camera.h"
World* Camera::world=NULL;

Camera::Camera(World* world){
	Camera::world=world;
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
void Camera::camera1(){
	gluLookAt(10,0,0,0,0,0,0,0,0);
}
void Camera::camera2(){
	gluLookAt(-10,0,0,
				0,0,0,
				0,0,0);
}
void Camera::camera3(){
	gluLookAt(0,10,0,
				0,0,0,
				0,0,0);
}
void Camera::camera4(){
	gluLookAt(0,-10,0,
				0,0,0
				0,0,0);
}
void Cammera::camera5(){
		gluLookAt(0,0,10,
				0,0,0
				0,0,0);
}
void Camera::camera6(){
		gluLookAt(0,0,-10,
				0,0,0
				0,0,0);
}
