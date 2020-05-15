#include "World.h"


void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
}

void World::fillObjects(){
    Point nave_point(0,0,-25);
    Point planet_point(10,30,0);
    Point satelite_point(30,8,50);
    Point sol_point(0,0,100);


    Point terra_point(5,15,0);
    Point lua_point(15,9,10);

    Point disco_nave_point(5,0,0);
    Point cupula_nave_point(2,10,-20);
    Point base_nave_point(0,-5,-10);

    /*Point planet_point(10,10,-50);
    Point satelite_point(30,8,-50);
    Point sol_point(0,0,-200);*/

    Point asteroide1_point(50,0,-50);
    Point asteroide2_point(-50,0,-50);
    Point asteroide3_point(0,20,-90);
    Point asteroide4_point(25,20,-20);

    Vector dir (1,1,1);
    Point center(0,0,0);


    Object* disco_nave = new DiscoNave(center);
    disco_nave->setPosition(disco_nave_point);
    disco_nave->setVelocity(0.0001);
    disco_nave->setDirection(dir);

    Object* cupula_nave = new CupulaNave(center);
    cupula_nave->setPosition(cupula_nave_point);
    cupula_nave->setVelocity(0.0001);
    cupula_nave->setDirection(dir);

    Object* base_nave = new BaseNave(center);
    base_nave->setPosition(base_nave_point);
    base_nave->setVelocity(0.0001);
    base_nave->setDirection(dir);

    Object* sol = new Sol(nave_point);
    sol->setPosition(sol_point);
    sol->setVelocity(0.f);
    sol->setSize(5);
    sol->setMass(10000);
    
    Object* planeta = new Planeta(nave_point);
    planeta->setPosition(planet_point);
    planeta->setVelocity(0.f);
    planeta->setMass(1000);
    planeta->applyGravityPull(sol);


    Object* satelite = new Satelite(planet_point);
    satelite->setPosition(satelite_point);
    satelite->setVelocity(0.f);
    satelite->setMass(10);
    satelite->applyGravityPull(sol);

    satelite->setForceToOrbit(sol,0.55);
    planeta->setForceToOrbit(sol,0.55);


    Object* terra = new Terra(nave_point);
    terra->setPosition(terra_point);
    terra->setVelocity(0.f);
    terra->setMass(1000);
    terra->applyGravityPull(sol);


    Object* lua = new Lua(terra_point);
    lua->setPosition(lua_point);
    lua->setVelocity(0.f);
    lua->setMass(10);
    lua->applyGravityPull(sol);

    lua->setForceToOrbit(sol,0.55);
    terra->setForceToOrbit(sol,0.55);


    satelite->setVelocity(0.6);
    planeta->setVelocity(5);
    terra->setVelocity(1.3);
    lua->setVelocity(10);


//--------------------------------------------------------------------

    Object* asteroide1 = new Asteroide1(sol_point);
    asteroide1->setPosition(asteroide1_point);
    asteroide1->setVelocity(0.01);

    Object* asteroide2 = new Asteroide1(sol_point);
    asteroide2->setPosition(asteroide2_point);
    asteroide2->setVelocity(0.01);


    Object* asteroide3 = new Asteroide2(sol_point);
    asteroide3->setPosition(asteroide3_point);
    asteroide3->setVelocity(0.01);
    asteroide3->setVelocity(0.0001);
    asteroide3->setDirection(dir);

    Object* asteroide4 = new Asteroide2(sol_point);
    asteroide4->setPosition(asteroide4_point);
    asteroide4->setVelocity(0.01);



    addObject(disco_nave);
    addObject(cupula_nave);
    addObject(base_nave);

    addObject(sol);
    addObject(satelite);
    addObject(planeta);

    addObject(terra);
    addObject(lua);

    addObject(asteroide1);
    addObject(asteroide2);
    addObject(asteroide3);
    addObject(asteroide4);

    //addObject(nave);
    main = base_nave;
}

World::~World(){
    for(Object* obj : objects){
        delete obj;
    }
    objects.clear();
}

Object* World::getMainObject(){
    return main;
} 

void World::draw(){
    for(Object* object : objects){
        object->draw();
    }
} 

void World::update(){
    for(Object * object : objects){
        object->update();
    }
}