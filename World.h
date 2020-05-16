#pragma once
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

//Cleanup needed
class World{
    public:
        World();
        ~World();
        Object* getMainObject();
        void draw();
        void update();

        void fillObjects();

        void addObject(Object* obj);

    private:
        Object* main;
        std::vector<Object*> objects;
};