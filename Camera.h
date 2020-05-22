#pragma onc
#include "World.h"
#include "utils.h"

#define CHANGE_SPEED 0.8	//Velocidade da nave
#define ZOOM_FACTOR 0.1 //Muda o zoom exponecialmente
#define ROTATION_SPEED 8
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
	void mover();
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
	void update();
	void changeCamera();

private:
	bool start;
	World* world;
	Point eye,center,up;
};