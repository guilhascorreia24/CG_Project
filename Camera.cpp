#include "Camera.h"

Camera::Camera(World* world) : eye(0,10,50),center(0,0,0),up(0,1,0){
	Camera::world = world;
	for(Object* obj : world->getMainObject()){
		Vector dir(0,0,-1);
		obj->setDirection(dir);
	}
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

void Camera::mover(){
	auto objects = world->getMainObject();
	for(auto object : objects){
		if(!object->canMove()){
			return;
		}
	}
	//printf("State Up Key->%d\n",hotkeys[GLUT_KEY_UP]);
	//printf("Key up->%d\n",GLUT_KEY_UP);
	if(getKeyState(GLUT_KEY_DOWN) == KEY_PRESSED){
		movimento_traz();
	}

	if(getKeyState(GLUT_KEY_UP) == KEY_PRESSED){
		movimento_frente();
	}

	if(getKeyState(GLUT_KEY_RIGHT)== KEY_PRESSED){
		movimento_direita();
	}

	if(getKeyState(GLUT_KEY_LEFT) == KEY_PRESSED){
		movimento_esquerda();
	}
}
void Camera::update(){
	//printf("State Up Key->%d\n",hotkeys[GLUT_KEY_UP]);
	//printf("Key up->%d\n",GLUT_KEY_UP);
	if(getSpecKeyState(GLUT_KEY_DOWN) == KEY_PRESSED){
		auto objects = world->getMainObject();
		for(auto object : objects){
			if(!object->canMove()){
				return;
			}
		}
		movimento_traz();
	}

	if(getSpecKeyState(GLUT_KEY_UP) == KEY_PRESSED){
		auto objects = world->getMainObject();
		for(auto object : objects){
			if(!object->canMove()){
				return;
			}
		}
		movimento_frente();
	}

	if(getSpecKeyState(GLUT_KEY_RIGHT)== KEY_PRESSED){
		auto objects = world->getMainObject();
		for(auto object : objects){
			if(!object->canMove()){
				return;
			}
		}
		movimento_direita();
	}

	if(getSpecKeyState(GLUT_KEY_LEFT) == KEY_PRESSED){
		auto objects = world->getMainObject();
		for(auto object : objects){
			if(!object->canMove()){
				return;
			}
		}
		movimento_esquerda();
	}
	changeCamera();
}

void Camera::keyboardCamera(int key, int x, int y){
	if(!start){
		return;
	}
	switch(key){
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
	//printf("Address %d\n",hotkeys);
	/*
	for(int i = 0; i<256;i++){
		if(getKeyState(i) == true){
			printf("Hotkey-> %d is Pressed\n",i);
		}
	}*/
	changeCamera();
}

void Camera::keyboardZoom(unsigned char key,int x, int y){
	if(!start){
		return;
	}
	switch(key){
		case '+':{
			Vector dir1(eye,center);
			dir1*=0.1;
			eye += dir1;
			break;
		}
		case '-':{
			Vector dir2(eye,center);
			dir2*=0.1;
			eye -= dir2;
			break;
		}
		default:
			break;
	}
	/*if(distance<=10){
		distance = 11;
		return;	
	}
	if(distance>400){
		distance = 399;
		return;	
	}*/
	changeCamera();
}
void Camera::changeCamera(){
	glLoadIdentity();
	gluLookAt(eye.x,eye.y,eye.z,center.x,center.y,center.z,up.x,up.y,up.z);
}
void Camera::camera1(){
	eye = Point(50,0,0);
	up = Point(0,1,0);
	//gluLookAt(distance,0,0,0,0,0,0,1,0);
}
void Camera::camera2(){
	eye = Point(-50,0,0);
	up = Point(0,1,0);
	//gluLookAt(-distance,0,0,0,0,0,0,1,0);
}
void Camera::camera3(){
	eye = Point(0,50,0);
	up = Point(1,0,0);
	//gluLookAt(0,distance,0,0,0,0,1,0,0);
}
void Camera::camera4(){
	eye = Point(0,-50,0);
	up = Point(1,0,0);
	//gluLookAt(0,-distance,0,0,0,0,1,0,0);
}
void Camera::camera5(){
	eye = Point(0,0,50);
	up = Point(1,0,0);
	//gluLookAt(0,0,distance,0,0,0,1,0,0);
}
void Camera::camera6(){
	eye = Point(0,0,-50);
	up = Point(1,0,0);
	//gluLookAt(0,0,-distance,0,0,0,1,0,0);
}


void Camera::movimento_direita(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.x += 5;
	// up.x += 5;
	for(Object * object : mainObjects){
        AngleRotation rot(0,ROTATION_SPEED,0);
        object->rotate(rot);
		object->moveForward(0);
    }
	eye.y-=10;
	float dist = eye.distance(center);
	center = mainObjects[0]->getPosition();
	Vector dir =  mainObjects[0]->getDirection();
	dir*=-dist;
	eye = center;
	eye +=dir;
	eye.y = 10;
}

void Camera::movimento_esquerda(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.x -= 5;
	// up.x -= 5;
	for(Object * object : mainObjects){
        AngleRotation rot(0,-ROTATION_SPEED,0);
        object->rotate(rot);
		object->moveForward(0);
    }
	eye.y-=10;
	float dist = eye.distance(center);
	center = mainObjects[0]->getPosition();
	Vector dir =  mainObjects[0]->getDirection();
	dir*=-dist;
	eye = center;
	eye +=dir;
	eye.y = 10;

}
void Camera::movimento_frente(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.z -= 5;
	// up.z -= 5;
	//distance -= 5;
	Vector dir =  mainObjects[0]->getDirection();
	dir*=CHANGE_SPEED;
	eye+=dir;
	center+=dir;
    for(Object * object : mainObjects){
        object->moveForward(CHANGE_SPEED);
		//object->mover(0,0,-CHANGE_SPEED);
    }
}
void Camera::movimento_traz(){
    std::vector<Object*> mainObjects = world->getMainObject();
    // eye.z += 5;
	// up.z += 5;
	//distance += 5;
	Vector dir =  mainObjects[0]->getDirection();
	dir*=-CHANGE_SPEED;
	eye+=dir;
	center+=dir;
    for(Object * object : mainObjects){
        object->moveForward(-CHANGE_SPEED);
		//object->mover(0,0,-CHANGE_SPEED);
    }
}