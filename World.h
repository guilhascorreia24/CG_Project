#pragma once
#include "Camera.h"
#include "Object.h"
#include <vector>
#include "DiscoNave.h"
#include "CupulaNave.h"
#include "BaseNave.h"
#include "Sol.h"
#include "Satelite.h"
#include "Planeta.h"
#include "Asteroide1.h"
#include "Asteroide2.h"
#include "Terra.h"
#include "Lua.h"
#include "Foguetao.h"

class Camera;
class World{
    public:
        World();
        ~World();
        std::vector<Object*> getMainObject();
        void draw();
        void update();

        void setCamera(Camera* cam);
        void fillObjects();
        void addMainObject(Object* obj);
        void addObject(Object* obj);
        int nivel;
        void aumentarNivel(int nivel);
        bool collision(Object* one,Object* two);
        bool comecou;
        bool perdeu;

    private:
        Sol* sol;
        std::vector<Object*> main;
        std::vector<Object*> objects;
        Camera *cam;

};