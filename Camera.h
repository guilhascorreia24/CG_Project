#pragma once
#include "utils.h"
#include "World.h"

#define CHANGE_SPEED 1.2	//Velocidade da nave
#define ZOOM_FACTOR 0.1 //Muda o zoom exponecialmente
#define UPP_OFFSET 10

class World;
class Camera{
public:
 Camera(World* w);
 void Start();
 void Stop();
 ~Camera();
 void keyboardCamera(int key,int x, int y);
 void keyboardZoom(unsigned char key, int x, int y);

 //Muda a camara para outra direção
 void mainPositionChange(Vector &a);
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
	void endireitar_nave();
	int Rotate;
private:
	bool isUpp;
	bool start;
	World* world;
	Point eye,center,up;
};