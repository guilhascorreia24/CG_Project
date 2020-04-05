#include "World.h"
#include "Camera.h"
#include "RotationHandler.h"
#include "Camera.h"
#include "utils.h"
#include "Nave.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define FRAME_DELTA 1000/150


#define PI 3.14159
//static GLfloat spin = 0.0;
int i, more;
bool pressed=false;
GLfloat angle, fAspect;
World* world;
RotationHandler* rot;
Camera* cam;
GLint Window;
GLfloat win;

GLfloat luzAmbiente[4];
bool iluminacao=true,shading=true,antialiasing=true;



void keyboardHandler(int key,int x, int y){
    rot->keyboardHandler(key,x,y);
    cam->keyboardCamera(key,x,y);
}

void teclas(unsigned char key, int x,int y){
    cam->keyboardZoom(key,x,y);
    switch (key)
    {
    case '1':
        Object::drawLabels = !Object::drawLabels;
        break;
    case 'w':
     glLoadIdentity();
        if(!pressed){pressed=true;}
        else{pressed=false;} 
        glLoadIdentity();
        //glutPostRedisplay()();
        break;      
    case 'a':
     rot->keyboardSpeed(key, x, y);
     break;
    case 'z':
        rot->keyboardSpeed(key,x,y);
        //glutPostRedisplay()();
        break;
    case 27:
        glutDestroyWindow(Window);
        //glutPostRedisplay()();
        exit(0);
        break;
    /*case '+':
        win -= 1;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           glOrtho(-win, win, -win, win, -win*2, win*2);
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
           
            if(cam->camara==1)
	           gluLookAt(50,0,0,0,0,0,0,1,0);
            else if(cam->camara==2)
	           gluLookAt(-50,0,0,0,0,0,0,1,0);
            else if(cam->camara==3)
	            gluLookAt(0,50,0,0,0,0,1,0,0);
            else if(cam->camara==4)
	            gluLookAt(0,-50,0,0,0,0,1,0,0);
            else if(cam->camara==5)
		        gluLookAt(0,0,50,0,0,0,1,0,0);
            else if(cam->camara==6)
		        gluLookAt(0,0,-50,0,0,0,1,0,0);
        //glutPostRedisplay()();

        break;

    case '-':
            win += 1;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           glOrtho(-win, win, -win, win, -win*2, win*2);
           glMatrixMode(GL_MODELVIEW);
           glLoadIdentity();
           

            if(cam->camara==1)
	           gluLookAt(50,0,0,0,0,0,0,1,0);
            else if(cam->camara==2)
	           gluLookAt(-50,0,0,0,0,0,0,1,0);
            else if(cam->camara==3)
	            gluLookAt(0,50,0,0,0,0,1,0,0);
            else if(cam->camara==4)
	            gluLookAt(0,-50,0,0,0,0,1,0,0);
            else if(cam->camara==5)
		        gluLookAt(0,0,50,0,0,0,1,0,0);
            else if(cam->camara==6)
		        gluLookAt(0,0,-50,0,0,0,1,0,0);
            //glutPostRedisplay()();
        break;*/ 
    }
 
}

void display(void)
{
    glMatrixMode(GL_MODELVIEW); 
    glPushMatrix(); 

    

    //glEnable(GL_TEXTURE_2D);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 //   glPushMatrix();


/*    glFrontFace(GL_CCW);
    glCullFace(GL_FRONT);
    glEnable(GL_CULL_FACE); */

/*    glTranslatef(-10.0,-10.0,0.0);  */
    //gluLookAt(0,0,100,0,0,0,0,0,0);
    glScalef(1.0,1.0,1.0);
   // glColor3f (1.0, 0.0, 0.0);


    if(iluminacao==true){    
        luzAmbiente[0]=0.2;
        luzAmbiente[1]=0.2;
        luzAmbiente[2]=0.2;
        luzAmbiente[3]=1.0; 
    }
    else{
        luzAmbiente[0]=0.0;
        luzAmbiente[1]=0.0;
        luzAmbiente[2]=0.0;
        luzAmbiente[3]=0.0; 
    }

    if (shading==false)
        glShadeModel (GL_FLAT);
    else
        glShadeModel(GL_SMOOTH);
    

    if (antialiasing==true){
        //glutSetOption(GL_MULTISAMPLE, 4);
        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV,GL_NICEST);
    }
    else{
       // glutSetOption(GL_MULTISAMPLE, 0);
        glDisable(GL_MULTISAMPLE);
    }
         

    if(pressed){
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    }else{
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    world->draw();
    //nave_sem_perna->draw();
    //glutSolidTeapot(1);


    glPopMatrix();
    glutSwapBuffers();
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 

}


void init(void)
{
    win=50;

    luzAmbiente[0]=0.2;
    luzAmbiente[1]=0.2;
    luzAmbiente[2]=0.2;
    luzAmbiente[3]=1.0; 

    GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );	



	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 



    // Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

//  	// Especifica que a cor de fundo da janela será preta
   // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);



    // Habilita o modelo de colorização de Gouraud
    glShadeModel(GL_SMOOTH);

    // Define a refletância do material
    glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
    // Define a concentração do brilho
    glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

    // Ativa o uso da luz ambiente
    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);


    // // Define os parâmetros da luz de número 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);





    // Habilita a definição da cor do material a partir da cor corrente
    glEnable(GL_COLOR_MATERIAL);
    //Habilita o uso de iluminação
    glEnable(GL_LIGHTING);
    // Habilita a luz de número 0
    glEnable(GL_LIGHT0);
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);


   glEnable(GLUT_MULTISAMPLE);

    Nave::inicializarTextura();
    Planeta::inicializarTextura();
    Sol::inicializarTextura();
    Satelite::inicializarTextura();
    world = new World();
    rot = new RotationHandler(world);
    cam= new Camera();
    rot->Start();
    cam->Start();


	
    
    //glClearColor (0.0, 0.0, 1.0, 0.0);
    //glShadeModel (GL_FLAT);
    glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(float)w/h,0.5,600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam->changeCamera();
}

// Função usada para especificar o volume de visualização
/*void EspecificaParametrosVisualizacao(void)
{
    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(45,fAspect,0.4,500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();

    // Especifica posição do observador e do alvo
    gluLookAt(0,0,50, 0,0,0, 0,1,0);
}*/
/*
// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if ( h == 0 ) h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);
 
    // Calcula a correção de aspecto
    fAspect = (GLfloat)w/(GLfloat)h;

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    int L = 100;

    if (w <= h)
        glOrtho(-L, L, -L * h / w, L * h / w, -L * 2, L * 2);
    else
        glOrtho(-L * w / h, L * w / h, -L, L, -L * 2, L * 2);

    glMatrixMode(GL_MODELVIEW);

}*/

void destroy(){
    delete rot;
    delete cam;
    delete world;
}
//----------------------------------------------------

// Gerenciamento do menu com as opções de cores           
void Menu_Flat_Wireframe(int op)
{
   switch(op) {
            case 0:
                    //glLoadIdentity();
                    pressed=true;
                    //glLoadIdentity();
                    break;
            case 1:
                    //glLoadIdentity();
                    pressed=false; 
                    //glLoadIdentity();
                    break;

    }
    glutPostRedisplay();
}           

// Gerenciamento do menu principal           
void MenuPrincipal(int op)
{
}
    

// Gerenciamento do menu com as opções de cores           
void Iluminacao(int op)
{
   switch(op) {
            case 0:
                    iluminacao=true;
                    break;
            case 1:
                    iluminacao=false;
                    break;
    }
    glutPostRedisplay();
}   
        

// Gerenciamento do menu com as opções de cores           
void GouraudShading(int op)
{
   switch(op) {
            case 0:
                    shading=true;
                    break;
            case 1:
                    shading=false;
                    break;
    }
    glutPostRedisplay();
}   
         

// Gerenciamento do menu com as opções de cores           
void Antialiasing(int op)
{
   switch(op) {
            case 0:
                     antialiasing=true;
                     break;
            case 1:
                     antialiasing=false;
                     break;

    }
    glutPostRedisplay();
}   
          
  


// Criacao do Menu
void CriaMenu() 
{
    int menu,submenu1,submenu2,submenu3,submenu4;
    //glLoadIdentity();
    submenu1 = glutCreateMenu(Menu_Flat_Wireframe);
    glutAddMenuEntry("Wireframe",0);
    glutAddMenuEntry("Flat",1);

    submenu2 = glutCreateMenu(Iluminacao);
    glutAddMenuEntry("ON",0);
    glutAddMenuEntry("OFF",1);

    submenu3 = glutCreateMenu(GouraudShading);
    glutAddMenuEntry("ON",0);
    glutAddMenuEntry("OFF",1);

    submenu4 = glutCreateMenu(Antialiasing);
    glutAddMenuEntry("ON",0);
    glutAddMenuEntry("OFF",1);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Flat ou Wireframe",submenu1);
    glutAddSubMenu("Iluminacao",submenu2);
    glutAddSubMenu("Gouraud Shading",submenu3);
    glutAddSubMenu("Antialiasing",submenu4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
      
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) 
            CriaMenu();
         
    glutPostRedisplay();
}
     

void mainloop(){
    static long last_time = glutGet(GLUT_ELAPSED_TIME);
    long currTime = glutGet(GLUT_ELAPSED_TIME);
    if(currTime-last_time>FRAME_DELTA){
        world->update();
        glutPostRedisplay();
        i = 0;
    }
    i++;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(350, 300);
    glutInitWindowPosition(100, 100);
    Window=glutCreateWindow(argv[0]);
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glewInit();
    init();

     int iMultiSample,iNumSample;
     glGetIntegerv(GL_SAMPLE_BUFFERS,&iMultiSample);
     glGetIntegerv(GL_SAMPLES,&iNumSample);
     //printf("-> %d %d",iMultiSample,iNumSample);
    // cout << "iMultiSample: " << iMultiSample << endl;
    // cout << "iNumSamples: " << iNumSample << endl;    


    glutMouseFunc(GerenciaMouse); 
    glutSpecialFunc(keyboardHandler);
	glutKeyboardFunc(teclas);
    glutIdleFunc(mainloop);
    glutMainLoop();
    destroy();
    return 0;
}


