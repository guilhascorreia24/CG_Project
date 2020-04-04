#include "World.h"

void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
}

void World::fillObjects(){
    Point center(0,0,0);
    Point Planet(3,3,0);
    Object* nave = new Nave();
    Object* meteoro = new Meteoro(center);
    nave->setPosition(center);
    Vector v(0,0,-1);
    nave->setDirection(v);
    meteoro->setPosition(Planet);
    meteoro->setVelocity(0.0);
    nave->setVelocity(0.0);

    addObject(nave);
    //addObject(meteoro);
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