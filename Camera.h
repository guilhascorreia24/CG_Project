#pragma once
#include "utils.h"
#include "World.h"
class Camera{
public:
 Camera(World* w);
 void Start();
 void Stop();
 ~Camera();
 void keyboardCamera(int key,int x, int y);
 void keyboardZoom(unsigned char key, int x, int y);
 int camara;
private:
	void camera1();
	void camera2();
	void camera3();
	void camera4();
	void camera5();
	void camera6();
	void movimento_direita();
    void movimento_frente();
	void movimento_esquerda();
    void movimento_traz();
public:
	void changeCamera();

private:
	bool start;
	World* world;
	int distance;
	Point eye,center,up;
	

};