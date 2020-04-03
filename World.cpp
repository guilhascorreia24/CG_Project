#include "World.h"

void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World(Object* obj) : main(obj){
    addObject(obj);
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