#pragma once
#include "utils.h"
#include "World.h"
class Camera{
public:
 Camera(World* w);
 ~Camera();
private:
	static void keyboardCamera(int key,int x, int y);
	static void camera1();
	static void camera2();
	static void camera3();
	static void camera4();
	static void camera5();
	static void camera6();
private:
	static World *world;

}