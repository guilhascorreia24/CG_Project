#pragma once
#include <vector>
#include "Object.h"
#include "Nave.h"
#include "Sol.h"
#include "Satelite.h"
#include "Planeta.h"



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
        Object* sun;
        std::vector<Object*> objects;
};