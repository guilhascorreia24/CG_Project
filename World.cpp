#include "World.h"

void World::addMainObject(Object* obj){
    main.push_back(obj);
}

void World::addObject(Object* obj){
    objects.push_back(obj);
}

World::World() : main(0){
    fillObjects();
    comecou = false;
    perdeu = false;
}

void World::setCamera(Camera* cam){
    this->cam = cam;
}

void World::fillObjects(){
    this->nivel = 1;

    Point dist_point(0,0,0);
    // Point foguetao_point(0,0,-5);
    Point nave_point(0,0,0);
    Point planet_point(0,0,-180);
    Point satelite_point(0,0,-150);
    Point sol_point(20,0,-100);
    // Point terra_point(0,0,0);
    // Point lua_point(0,0,-120);

    // //----
    Point foguetao_point(10,0,-50);
    // Point planet_point(10,0,0);
    // Point satelite_point(30,0,50);


    Point terra_point(10,0,-55);
    Point lua_point(10,0,-50);
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
    terra->setUniformOrbit(sol,0.9,0.3);
    // terra->setForceToOrbit(sol,0.55,0.20);
    // terra->setVelocity(1);


    Lua* lua = new Lua(terra_point);
    lua->setPosition(lua_point);
    lua->setVelocity(0.05);
    lua->setMass(10);
    lua->setUniformOrbit(terra,0.9,1);
    terra->update();

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
    foguetao->disablePhisycs();
    Point p = terra->getPosition();
    foguetao->setPosition(p);
    foguetao->setVelocity(0.3);
    //foguetao->setUniformOrbit(sol,0.9,1);
    foguetao->setSizeObject();
    //Vector direcao (0.0,1,0.0);
    //foguetao->setDirection(direcao);

//--------------------------------------------------------------------



    // terra->setUniformOrbit(sol,0.9,1);
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
    this->sol = sol;
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

bool World::collision(Object* one,Object* two){

    bool result = false;

    //printf("size %f %f %f\n",one->getSizeObject().x,one->getSizeObject().y,one->getSizeObject().z);
    // printf("min %f %f %f\n",one->min.x,one->min.y,one->min.z);
    // printf("max %f %f %f\n",one->max.x,one->max.y,one->max.z);
    // printf("posicao nave = %f %f %f \n",two->getPosition().x,two->getPosition().y,two->getPosition().z);
    // printf("posicao outro = %f %f %f \n\n\n",one->getPosition().x,one->getPosition().y,one->getPosition().z);
    if(two->getPosition().x-two->getSizeObject().x <= one->getPosition().x + (one->getSizeObject().x/2) && one->getPosition().x - (one->getSizeObject().x/2) <= two->getPosition().x+two->getSizeObject().x
    &&
    two->getPosition().z-two->getSizeObject().z <= one->getPosition().z + one->getSizeObject().z && one->getPosition().z - one->getSizeObject().z <= two->getPosition().z+two->getSizeObject().z)
        result = true;
    
    return result;
}

void World::draw(){
    Point a = sol->getPosition();
    GLfloat posicaoLuz[4] = {a.x,a.y,a.z, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    
    for(Object* object : objects){
        object->draw();
    }
    
    for(Object* object : main){
        object->draw();
    }

} 


void World::update(){
    for(Object * object : objects){
        object->update();
        for(Object* parte : main){
            if(parte->comecou)
                this->comecou = true;
            bool c=collision(object, parte);
            if(c){
                parte->colidiu=true;
                 if(parte->velocity>0)
                    parte->velocity-=0.00001;
                    }
                if(parte->perdeu)  
                    perdeu = true;      
        }
    }
    bool set = false;
    for(Object * object : main){
        object->update();
        if(object->getPosition().z>=250)//Zmax
        {
            Point tmp(object->getPosition().x,object->getPosition().y,-250);
            if(!set){
                Point pos = object->getPosition();
                Vector d(pos,tmp);
                cam->mainPositionChange(d);
                set = true;
            }
            object->setPosition(tmp);
            
        }
        else if(object->getPosition().z<=-250)//Zmin
        {
            Point tmp(object->getPosition().x,object->getPosition().y,250);
            if(!set){
                Point pos = object->getPosition();
                Vector d(pos,tmp);
                cam->mainPositionChange(d);
                set = true;
            }
            object->setPosition(tmp);
        }

        if(object->getPosition().x>=250)//Xmax
        {
            Point tmp(-250,object->getPosition().y,object->getPosition().z);
            if(!set){
                Point pos = object->getPosition();
                Vector d(pos,tmp);
                cam->mainPositionChange(d);
                set = true;
            }
            object->setPosition(tmp);
        }
        else if (object->getPosition().x<=-250)//Xmin
        {
            Point tmp(250,object->getPosition().y,object->getPosition().z);
            if(!set){
                Point pos = object->getPosition();
                Vector d(pos,tmp);
                cam->mainPositionChange(d);
                set = true;
            }
            object->setPosition(tmp);
        }
    }
    
}


    void World::aumentarNivel(int nivel){
        printf("INN\n");
        Point asteroide_point(25,20,-20);
        for(int i = 0; i < 20 ; i++){
            int intervalo = i*4+nivel*2;
            printf("Intervalo->%d\n",intervalo);

            if (i%2==0)
                asteroide_point = Point(intervalo,0,-20);
            else          
                asteroide_point = Point(25,0,-intervalo);

            Asteroide1* asteroide1 = new Asteroide1(asteroide_point);
            asteroide1->setPosition(asteroide_point);
            asteroide1->setVelocity(0.01);
            asteroide1->setUniformOrbit(sol,0.9,1);

            asteroide1->setSizeObject();
            asteroide1->setSizeObject();
            addObject(asteroide1);
        }
    }