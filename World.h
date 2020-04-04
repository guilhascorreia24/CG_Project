#pragma once
#include <vector>
#include "Object.h"
#include "Nave.h"
#include "Satelite.h"
#include "Planeta.h"
#include "Sol.h"



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