#include "ControladorNave.h"


ControladorNave::ControladorNave(World* world){
    ControladorNave::world = world;
    start = false;
    colidiu = false;
}

ControladorNave::~ControladorNave(){
    printf("Destructed\n");
    Stop();
}

void ControladorNave::Start(){
    start = true;
}

void ControladorNave::Stop(){
    start = false;
}

void ControladorNave::keyboardHandler(int key,int x, int y){
    if(!start){
        return;
    }
    switch(key){
        case GLUT_KEY_DOWN:
            printf("oii");
            movimento_traz();
            break;
        case GLUT_KEY_UP:
            printf("oii");
            movimento_frente();
            break;

        case GLUT_KEY_LEFT:
            printf("oii");
            movimento_esquerda();
            break;
        case GLUT_KEY_RIGHT:
            printf("oii");
            movimento_direita();
            break;
        default:
        break;
    }
}

// void ControladorNave::keyboardSpeed(unsigned char key, int x,int y){
//     if(!start){return;}
//     switch(key){
//         case 'a':
//             moreSpeed();
//             break;
//         case 'z':
//             lessSpeed();
//             break;
//     }
// }

void ControladorNave::movimento_direita(){
    printf("oii 1");
    // Object* mainObject = world->getMainObject();
    // AngleRotation rot(0,Rotate,0);
    // mainObject->rotate(rot);
}

void ControladorNave::movimento_esquerda(){
    printf("oii 2");
    // Object* mainObject = world->getMainObject();
    // AngleRotation rot(0,-Rotate,0);
    // mainObject->rotate(rot);

}
void ControladorNave::movimento_frente(){
    printf("oii 3");
    // Object* mainObject = world->getMainObject();
    // AngleRotation rot(Rotate,0,0);
    // mainObject->rotate(rot);
}
void ControladorNave::movimento_traz(){
    printf("oii 4");
    // Object* mainObject = world->getMainObject();
    // AngleRotation rot(-Rotate,0,0);
    // mainObject->rotate(rot);
}

// void ControladorNave::moreSpeed(){
//     Rotate++;
// }
// void ControladorNave::lessSpeed(){
//     if(Rotate>0)
//         Rotate--;
//     else
//         Rotate=0;
// }