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
private:
	void camera1();
	void camera2();
	void camera3();
	void camera4();
	void camera5();
	void camera6();

private:
	bool start;

};