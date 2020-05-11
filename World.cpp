#include "World.h"


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


    Object* disco_nave = new DiscoNave(nave_point);
    disco_nave->setPosition(disco_nave_point);
    disco_nave->setVelocity(0.f);

    Object* cupula_nave = new CupulaNave(nave_point);
    cupula_nave->setPosition(cupula_nave_point);
    cupula_nave->setVelocity(0.f);

    Object* base_nave = new BaseNave(nave_point);
    base_nave->setPosition(base_nave_point);
    base_nave->setVelocity(0.f);

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

    satelite->setForceToOrbit(sol,1.55);
    planeta->setForceToOrbit(sol,1.55);

    satelite->setVelocity(1.3);
    planeta->setVelocity(10);


//--------------------------------------------------------------------

    Object* asteroide1 = new Asteroide1(sol_point);
    asteroide1->setPosition(asteroide1_point);
    asteroide1->setVelocity(0.0f);

    Object* asteroide2 = new Asteroide1(sol_point);
    asteroide2->setPosition(asteroide2_point);
    asteroide2->setVelocity(0.0f);


    Object* asteroide3 = new Asteroide2(sol_point);
    asteroide3->setPosition(asteroide3_point);
    asteroide3->setVelocity(0.0f);

    Object* asteroide4 = new Asteroide2(sol_point);
    asteroide4->setPosition(asteroide4_point);
    asteroide4->setVelocity(0.0f);



    addObject(disco_nave);
    addObject(cupula_nave);
    addObject(base_nave);

    addObject(sol);
    addObject(satelite);
    addObject(planeta);


    addObject(asteroide1);
    addObject(asteroide2);
    addObject(asteroide3);
    addObject(asteroide4);

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
        object->update();
    }
}