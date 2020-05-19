#include "Camera.h"

Camera::Camera(World* world) : eye(0,0,1),center(0,0,0),up(0,1,0){
	Camera::world = world;
	distance = 50;
}

Camera::~Camera(){
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
		case GLUT_KEY_DOWN:
            movimento_traz();
            break;
        case GLUT_KEY_UP:
            
            movimento_frente();
            break;

        case GLUT_KEY_LEFT:
            
            movimento_esquerda();
            break;
        case GLUT_KEY_RIGHT:
            
            movimento_direita();
            break;
		case GLUT_KEY_F2:
		     
			camera1();
			// Camera=1;
			    
			break;
		case GLUT_KEY_F3:
		     
			camera2();
			// Camera=2;
			    
			break;
		case GLUT_KEY_F4:
		     
			camera3();
			// Camera=3;
			    
			break;
		case GLUT_KEY_F5:
		     
			camera4();
			// Camera=4;
			    
			break;
		case GLUT_KEY_F6:
		     
			camera5();
			// Camera=5;
			    
			break;
		case GLUT_KEY_F7:
		     
			camera6();
			// Camera=6;
			    
			break;		
	}
	changeCamera();
}

void Camera::keyboardZoom(unsigned char key,int x, int y){
	if(!start){
		return;
	}
	switch(key){
		case '+':
			distance-=2;
			break;
		case '-':
			distance+=2;
			break;
		default:
			break;
	}
	if(distance<=10){
		distance = 11;
		return;	
	}
	if(distance>400){
		distance = 399;
		return;	
	}
	changeCamera();
}
void Camera::changeCamera(){
	glLoadIdentity();
	gluLookAt(distance*eye.x,distance*eye.y,distance*eye.z,center.x,center.y,center.z,up.x,up.y,up.z);
}
void Camera::camera1(){
	eye = Point(1,0,0);
	up = Point(0,1,0);
	//gluLookAt(distance,0,0,0,0,0,0,1,0);
}
void Camera::camera2(){
	eye = Point(-1,0,0);
	up = Point(0,1,0);
	//gluLookAt(-distance,0,0,0,0,0,0,1,0);
}
void Camera::camera3(){
	eye = Point(0,1,0);
	up = Point(1,0,0);
	//gluLookAt(0,distance,0,0,0,0,1,0,0);
}
void Camera::camera4(){
	eye = Point(0,-1,0);
	up = Point(1,0,0);
	//gluLookAt(0,-distance,0,0,0,0,1,0,0);
}
void Camera::camera5(){
	eye = Point(0,0,1);
	up = Point(1,0,0);
	//gluLookAt(0,0,distance,0,0,0,1,0,0);
}
void Camera::camera6(){
	eye = Point(0,0,-1);
	up = Point(1,0,0);
	//gluLookAt(0,0,-distance,0,0,0,1,0,0);
}


void Camera::movimento_direita(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.x += 5;
	// up.x += 5;
	center.x -= 5;
    for(Object * object : mainObjects){
        object->mover(5,0,0);
    }
}

void Camera::movimento_esquerda(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.x -= 5;
	// up.x -= 5;
	center.x += 5;
    for(Object * object : mainObjects){
        object->mover(-5,0,0);
    }

}
void Camera::movimento_frente(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.z -= 5;
	// up.z -= 5;
	distance -= 5;
	center.z -= 5;
    for(Object * object : mainObjects){
        object->mover(0,0,-5);
    }
}
void Camera::movimento_traz(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.z += 5;
	// up.z += 5;
	distance += 5;
	center.z += 5;
    for(Object * object : mainObjects){
        object->mover(0,0,5);
    }
}