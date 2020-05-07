#include "World.h"
#define SUN_GRAVITY 1

void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
}

void World::fillObjects(){
    Point nave_point(0,0,-25);
    Point planet_point(10,30,-100);
    Point satelite_point(30,8,-50);
    Point sol_point(0,0,0);


    Object* sol = new Sol(nave_point);
    sol->setPosition(sol_point);
    sol->setVelocity(0.f);
    sol->setSize(5);
    sol->setMass(10000);

    Object* nave = new Nave();
    nave->setPosition(nave_point);
    nave->setMass(100);
    nave->applyGravityPull(sol);
    
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

    nave->setForceToOrbit(sol,1.55);
    satelite->setForceToOrbit(sol,1.55);
    planeta->setForceToOrbit(sol,1.55);

    nave->setVelocity(1);
    satelite->setVelocity(0.1);


    addObject(nave);
    addObject(sol);
    addObject(satelite);
    addObject(planeta);
    //addObject(nave);
    main = sol;
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
        object->update(getTimeInMili());
    }
}
