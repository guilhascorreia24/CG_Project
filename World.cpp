#include "World.h"


void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
}

void World::fillObjects(){
    Point nave_point(0,0,0);
    Point planet_point(10,10,-2);
    Point satelite_point(12,8,0);
    Point sol_point(-8,5,0);

    Object* nave = new Nave();
    nave->setPosition(nave_point);

    Object* sol = new Sol(nave_point);
    sol->setPosition(sol_point);
    sol->setVelocity(0.0);
    sol->setSize(3);
    
    Object* planeta = new Planeta(nave_point);
    planeta->setPosition(planet_point);
    planeta->setVelocity(0.1);

    Object* satelite = new Satelite(sol_point);
    satelite->setPosition(satelite_point);
    satelite->setVelocity(0.1);

    addObject(nave);
    addObject(sol);
    addObject(satelite);
    addObject(planeta);
    //addObject(nave);
    main = nave;
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