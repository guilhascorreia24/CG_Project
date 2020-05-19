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
#include "utils.h"

//Cleanup needed
class World{
    public:
        World();
        ~World();
        std::vector<Object*> getMainObject();
        void draw();
        void update();

        void fillObjects();
        void addMainObject(Object* obj);
        void addObject(Object* obj);

    private:
        Sol *sol;
        Terra *terra;
        std::vector<Object*> main;
        std::vector<Object*> objects;
};