#pragma once
#include "utils.h"
#include "World.h"
class Camera{
public:
 Camera();
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
public:
	void changeCamera();

private:
	bool start;
	int distance;
	Point eye,center,up;
	

};