#pragma once
#include <vector>
#include "Object.h"


//Cleanup needed
class World{
    public:
        World(Object* obj);
        ~World();
        Object* getMainObject();
        void draw();

        void addObject(Object* obj);

    private:
        Object* main;
        std::vector<Object*> objects;
};