#include "World.h"

void World::addMainObject(Object* obj){
    main.push_back(obj);
}

void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
}

void World::fillObjects(){
    this->nivel = 1;

    Point dist_point(0,0,0);
    // Point foguetao_point(0,0,-5);
    Point nave_point(0,0,-25);
    Point planet_point(0,0,-30);
    Point satelite_point(0,0,-50);
    Point sol_point(20,0,-200);
    // Point terra_point(0,0,0);
    // Point lua_point(0,0,-120);

    // //----
    Point foguetao_point(10,0,-5);
    // Point planet_point(10,0,0);
    // Point satelite_point(30,0,50);


    Point terra_point(10,0,-5);
    Point lua_point(15,0,-10);
    // //----

    Point disco_nave_point(5,0,0);
    Point cupula_nave_point(2,10,-20);
    Point base_nave_point(0,-5,-10);

    /*Point planet_point(10,10,-50);
    Point satelite_point(30,8,-50);
    Point sol_point(0,0,-200);*/

    Point asteroide1_point(50,0,-50);
    Point asteroide2_point(-50,0,-50);
    Point asteroide3_point(0,0,-90);
    Point asteroide4_point(25,0,-20);

    Vector dir (1,1,1);
    Point center(0,0,0);


    DiscoNave* disco_nave = new DiscoNave(center,disco_nave_point);
    disco_nave->setPosition(disco_nave_point);
    disco_nave->setVelocity(0.11);
    disco_nave->setDirection(dir);
    disco_nave->setSizeObject();
    disco_nave->disablePhisycs();

    CupulaNave* cupula_nave = new CupulaNave(center,cupula_nave_point);
    cupula_nave->setPosition(cupula_nave_point);
    cupula_nave->setVelocity(0.11);
    cupula_nave->setDirection(dir);
    cupula_nave->setSizeObject();
    cupula_nave->disablePhisycs();

    BaseNave* base_nave = new BaseNave(center,base_nave_point);
    base_nave->setPosition(base_nave_point);
    base_nave->setVelocity(0.11);
    base_nave->setDirection(dir);
    base_nave->setSizeObject();
    base_nave->disablePhisycs();

    Sol* sol = new Sol(nave_point);
    sol->setPosition(sol_point);
    sol->setVelocity(0.f);
    sol->setSize(5);
    sol->setMass(10000);
    sol->setSizeObject();


    
    
    Planeta* planeta = new Planeta(nave_point);
    planeta->setPosition(planet_point);
    planeta->setVelocity(0.f);
    planeta->setMass(1000);
    //planeta->applyGravityPull(sol);
    //planeta->setForceToOrbit(sol,0.55,0.15);
    planeta->setUniformOrbit(sol,0.9,1);
    planeta->setSizeObject();


    Satelite* satelite = new Satelite(satelite_point);
    satelite->setPosition(satelite_point);
    satelite->setVelocity(0.f);
    satelite->setMass(10);
    satelite->setUniformOrbit(sol,0.9,1);
    satelite->setSizeObject();


    Terra* terra = new Terra(nave_point);
    terra->setPosition(terra_point);
    terra->setVelocity(0.f);
    terra->setMass(100);
    terra->setSizeObject();
    
    // terra->setUniformOrbit(sol,0.9,1);
    // terra->setForceToOrbit(sol,0.55,0.20);
    // terra->setVelocity(1);


    Lua* lua = new Lua(terra_point);
    lua->setPosition(lua_point);
    lua->setVelocity(0.05);
    lua->setMass(10);
    //lua->setUniformOrbit(sol,0.9,1);

    // lua->setForceToOrbit(sol,0.55);
    // terra->setForceToOrbit(sol,0.55);
    lua->setSizeObject();
    //terra->setVelocity(2);
    //satelite->setVelocity(0.6);
    //planeta->setVelocity(5);
    //terra->setVelocity(1.3);
    //lua->setVelocity(10);





//--------------------------------------------------------------------

    Asteroide1* asteroide1 = new Asteroide1(sol_point);
    asteroide1->setPosition(asteroide1_point);
    asteroide1->setVelocity(0.01);
    asteroide1->setUniformOrbit(sol,0.9,1);

    asteroide1->setSizeObject();
    asteroide1->setSizeObject();
    // Point tmp = asteroide1->getSizeObject();
    // printf("%f %f %f",tmp.x,tmp.y,tmp.z);

    Asteroide1* asteroide2 = new Asteroide1(sol_point);
    asteroide2->setPosition(asteroide2_point);
    asteroide2->setVelocity(0.01);
    asteroide2->setUniformOrbit(sol,0.9,1);
    asteroide2->setSizeObject();

    Asteroide2* asteroide3 = new Asteroide2(sol_point);
    asteroide3->setPosition(asteroide3_point);
    asteroide3->setVelocity(0.01);
    asteroide3->setUniformOrbit(sol,0.9,1);
    asteroide3->setSizeObject();

    Asteroide2* asteroide4 = new Asteroide2(sol_point);
    asteroide4->setPosition(asteroide4_point);
    asteroide4->setVelocity(0.01);
    asteroide4->setUniformOrbit(sol,0.9,1);
    asteroide4->setSizeObject();


    Foguetao* foguetao = new Foguetao(foguetao_point);
    foguetao->setPosition(foguetao_point);
    foguetao->setVelocity(0.3);
    //foguetao->setUniformOrbit(sol,0.9,1);
    foguetao->setSizeObject();
    Vector direcao (1,1,1);
    foguetao->setDirection(direcao);

//--------------------------------------------------------------------



    // addObject(disco_nave);
    // addObject(cupula_nave);
    // addObject(base_nave);

    addObject(sol);
    addObject(satelite);
    addObject(planeta);

    addObject(terra);
    addObject(lua);

    addObject(asteroide1);
    addObject(asteroide2);
    addObject(asteroide3);
    addObject(asteroide4);

    addObject(foguetao);

    //addObject(nave);
    addMainObject(disco_nave);
    addMainObject(cupula_nave);
    addMainObject(base_nave);

    //sol->applyGravityPull(terra);
    //terra->setVelocity(10);
    //printf("%lf\n",terra->getVelocity());
    //getchar();

    //this->terra = terra;
    //this->sol = sol;
}

World::~World(){
    for(Object* obj : objects){
        delete obj;
    }
    objects.clear();
}

std::vector<Object*> World::getMainObject(){
    return main;
} 

void World::draw(){
    for(Object* object : objects){
        object->draw();
    }
    for(Object* object : main){
        object->draw();
    }

} 


void World::update(){
    /*static bool t = false;
    if(t)
        return;
    
    t = true;

    printf("Sun Position->");
    sol->getPosition().print();
    printf("Earth Position->");
    terra->getPosition().print();
    Point tmp = sol->getPosition();
    Point tmo2 = terra->getPosition();
    Vector v(tmp,tmo2);
    printf("Earth to Sun->");
    v.print();

    printf("Earth Direction->");
    terra->getDirection().print();

    printf("Earth Velocity->%f\n",terra->getVelocity());*/
    for(Object * object : objects){
        object->update();

        // para verificar a colisao
        Point po = object->getPosition();
        Point po_size = object->getSizeObject();
        // printf("%f\n",po_size.x);
        for(Object* parte : main){
            Point pp = parte->getPosition();
            Point pp_size = parte->getSizeObject();
            // Collision x
            bool collisionX = po.x + po_size.x >= pp.x &&
                pp.x + pp_size.x >= po.x;
            // Collision y
            bool collisionY = po.y + po_size.y >= pp.y &&
                pp.y + pp_size.y >= po.y;
            // Collision z
            bool collisionZ = po.z + po_size.z >= pp.z &&
                pp.z + pp_size.z >= po.z;
            if( collisionX && collisionY && collisionY ){
                //printf("colidiu");
                parte->colidiu=true;
            }
        }
    }
    for(Object * object : main){
        object->update();
    }
}
    /*

    */

    void World::aumentarNivel(int nivel){
        Point nave_point(0,0,-25);
        Point asteroide_point(25,20,-20);
        Point sol_point(0,0,70);
        Sol* sol = new Sol(nave_point);
        sol->setPosition(sol_point);
        sol->setVelocity(0.f);
        sol->setSize(5);
        sol->setMass(10000);

        sol->setSizeObject();
        printf("oi");
        for(int i = 20; i < 20 ; i++){
            int intervalo = i*4+nivel*2;

            if (i%2==0)
                Point asteroide_point(intervalo,20,-20);
            else          
                Point asteroide_point(25,20,-intervalo);

            Asteroide1* asteroide1 = new Asteroide1(sol_point);
            asteroide1->setPosition(asteroide_point);
            asteroide1->setVelocity(0.01);
            asteroide1->setUniformOrbit(sol,0.9,1);

            asteroide1->setSizeObject();
            asteroide1->setSizeObject();
            addObject(asteroide1);
        }
    }
