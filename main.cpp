#include "World.h"

#include "Camera.h"

#include "RotationHandler.h"

#include <string>

#include "Terra.h"

#include "Lua.h"

#include "utils.h"

#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define FRAME_DELTA 1000 / 30

GLuint texture=0;

int i, more;

bool pressed = false;

GLfloat angle, fAspect;

World *world;

RotationHandler *rot;

Camera *cam;

long time_elapsed ;

GLint Window;

GLfloat win;

GLfloat luzAmbiente[4];

long stop_time = 0;

int nivel=1;

bool iluminacao = true, shading = true, antialiasing = true;

bool ganhou = false, ajuda = false, mudou_de_nivel=false, tempo_restante = true;



// Função callback chamada pela GLUT a cada intervalo de tempo
void Timer(int value)
{
    mudou_de_nivel=true;
    nivel++;
    if(nivel==5){
        if(!world->perdeu)
        ganhou=true;
    }

}


void keyboardHandler(int key, int x, int y)
{

    cam->keyboardCamera(key, x, y);

    switch(key){
		case GLUT_KEY_F1:
            if(ajuda == false)  
			    ajuda = true;
            else
            {
                ajuda = false;
            }
   
			break;

	}
}

void teclas(unsigned char key, int x, int y)
{

    rot->keyboardHandler(key, x, y);

    if(world->comecou&&!ganhou&&!world->perdeu)
        cam->keyboardZoom(key, x, y);

    switch (key)

    {

    case 'l':

        Object::drawLabels = !Object::drawLabels;

        break;

    case 'w':

        glLoadIdentity();

        if (!pressed)
        {
            pressed = true;
        }

        else
        {
            pressed = false;
        }

        glLoadIdentity();

        break;

    case 'a':

        rot->keyboardSpeed(key, x, y);

        break;

    case 'z':

        rot->keyboardSpeed(key, x, y);

        break;

    case 27:

        glutDestroyWindow(Window);

        exit(0);

        break;
    case 32:
        if(mudou_de_nivel==true){
            mudou_de_nivel=false;
            glutTimerFunc(30000,Timer, 1);
            world->aumentarNivel(nivel);
            }
        break;
    }
}

void textura_fundo()
{
    int n;
    int width,height;
    unsigned char *dados = stbi_load("img/fundo.jpg", &width, &height, &n, 0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, dados);
    stbi_image_free(dados);
}

void desenha_fundo()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);



    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
     gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));
    glMatrixMode(GL_MODELVIEW);
     glPushMatrix();
    glLoadIdentity();

//     glColor4f(1.0, 1.0, 0.0, 0.5);


// // //-----




    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);

    glTexCoord2i(0,0);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH), 0);
    
    
    glTexCoord2i(1,0);
    glVertex2i(0,0);

    glTexCoord2i(1,1);
    glVertex2i(0,glutGet(GLUT_WINDOW_HEIGHT));


    glTexCoord2i(0,1);
    glVertex2i(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
    glEnd();

    glDisable(GL_TEXTURE_2D); 

// //-----




    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    
}

void display(void)

{

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    
    //glEnable(GL_TEXTURE_2D);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    

    glScalef(1.0, 1.0, 1.0);
    
    // glColor3f (1.0, 0.0, 0.0);




    if (iluminacao == true)
    {

        luzAmbiente[0] = 0.2;

        luzAmbiente[1] = 0.2;

        luzAmbiente[2] = 0.2;

        luzAmbiente[3] = 1.0;
        glEnable(GL_LIGHT0);
    }

    else
    {

        luzAmbiente[0] = 0.0;

        luzAmbiente[1] = 0.0;

        luzAmbiente[2] = 0.0;

        luzAmbiente[3] = 0.0;
        glDisable(GL_LIGHT0);
    }

    if (shading == false)

        glShadeModel(GL_FLAT);

    else

        glShadeModel(GL_SMOOTH);
    
    //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    if (antialiasing == true)
    {

        //glutSetOption(GL_MULTISAMPLE, 4);

        glEnable(GL_MULTISAMPLE);

        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
    }

    else
    {

        // glutSetOption(GL_MULTISAMPLE, 0);

        glDisable(GL_MULTISAMPLE);
    }

    if (pressed)
    {

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    //desenha_fundo();
    if(!ajuda&&!mudou_de_nivel&&!ganhou&&!world->perdeu){
        world->draw();}


//---------------
    
    if (ganhou)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
    
                glBegin(GL_QUADS);
                glColor4f(0.0, 1, 0.0, 0.1);
                glVertex2i(0, 1920);
                glVertex2i(0, 0);
                glVertex2i(1920, 0);
                glVertex2i(1920, 1920);
                glEnd();
                glColor3f(0.0, 1.0, 0.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(450, 520);

//******
                std::string s = "Ganhou!";
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
//******

                // s = "Para jogar outra vez pressione a tecla Space";
                // font = GLUT_BITMAP_HELVETICA_12;
                // glRasterPos2i(330+glutGet(GLUT_WINDOW_WIDTH)*0.04, 480-glutGet(GLUT_WINDOW_HEIGHT)*0.03);
                // for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                // {
                //     char c = *i;
                //     glutBitmapCharacter(font, c);
                // }
                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glDisable(GL_BLEND);
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
            }
            else if (world->perdeu)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
    
                glBegin(GL_QUADS);
                glColor4f(1.0, 0, 0.0, 0.1);
                glVertex2i(0, 1920);
                glVertex2i(0, 0);
                glVertex2i(1920, 0);
                glVertex2i(1920, 1920);
                glEnd();
                glColor3f(1.0, 0.0, 0.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(450, 520);

//******
                std::string s = "Perdeu!";
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
//******

                // s = "Para jogar outra vez pressione a tecla Space";
                // font = GLUT_BITMAP_HELVETICA_12;
                // glRasterPos2i(330+glutGet(GLUT_WINDOW_WIDTH)*0.04, 480-glutGet(GLUT_WINDOW_HEIGHT)*0.03);
                // for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                // {
                //     char c = *i;
                //     glutBitmapCharacter(font, c);
                // }
                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glDisable(GL_BLEND);
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
                
            }
            else if (mudou_de_nivel)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                glBegin(GL_QUADS);
                glColor4f(0.184314, 0.309804, 0.309804, 0.0);
                glVertex2i(100, 900);
                glVertex2i(100, 750);
                glVertex2i(900, 750);
                glVertex2i(900, 900);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(400+glutGet(GLUT_WINDOW_WIDTH)*0.05, 820-glutGet(GLUT_WINDOW_HEIGHT)*0.02);

//******
                std::string n = std::to_string(nivel);
                std::string s = "Nivel "+n;
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
//******

                glBegin(GL_QUADS);
                glColor4f(1.0, 1.0, 1.0, 0.0);
                glVertex2i(100, 750);
                glVertex2i(100, 500);
                glVertex2i(900, 500);
                glVertex2i(900, 750);
                glEnd();
                double intervalo = 10 + glutGet(GLUT_WINDOW_WIDTH)*0.03;
                double x = 300;
                double y = 600;

                s = "Pressione Space para continuar no nivel seguinte";
                glColor3f(0.0, 0.0, 0.0);
                font = GLUT_BITMAP_HELVETICA_12;
                
                glRasterPos2i(x + (intervalo*2), y + (intervalo*1));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
               


                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
            }


            if (!world->comecou)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                glColor3f(1.0, 1.0, 1.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(250+glutGet(GLUT_WINDOW_WIDTH)*0.05, 820-glutGet(GLUT_WINDOW_HEIGHT)*0.02);

//******
                std::string n = std::to_string(nivel);
                std::string s = "Preparado para uma viagem espacial?";
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
//******


                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
            }

            if (ajuda)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                glBegin(GL_QUADS);
                glColor4f(0.184314, 0.309804, 0.309804, 0.0);
                glVertex2i(100, 900);
                glVertex2i(100, 750);
                glVertex2i(900, 750);
                glVertex2i(900, 900);
                glEnd();
                glColor3f(1.0, 1.0, 1.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(350+glutGet(GLUT_WINDOW_WIDTH)*0.05, 820-glutGet(GLUT_WINDOW_HEIGHT)*0.02);

//******
                std::string s = "Ajudas do Jogo";
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
//******

                glBegin(GL_QUADS);
                glColor4f(1.0, 1.0, 1.0, 0.0);
                glVertex2i(100, 750);
                glVertex2i(100, 100);
                glVertex2i(900, 100);
                glVertex2i(900, 750);
                glEnd();
                double intervalo = 10 + glutGet(GLUT_WINDOW_WIDTH)*0.02;
                double x = 200;
                double y = 700;

                s = "Inclinar a nave para baixo: Tecla 'b'";
                glColor3f(0.0, 0.0, 0.0);
                font = GLUT_BITMAP_HELVETICA_12;
                
                glRasterPos2i(x + intervalo*2 , y - (intervalo*1));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
                
                s = "Inclinar a nave para cima: Tecla 'c'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*2));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }






                s = "Rodar a nave  para a direita: Tecla 'd'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*3));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Rodar a nave  para a esquerda: Tecla 'e'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*4));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }





                s = "Aumentar a velocidade da nave: Tecla 'a'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*5));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Diminuir a velocidade da nave: Tecla 'z'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*6));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }




                s = "Movimentar a nave para a frente: Tecla 'Seta para Cima'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*8));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Movimentar a nave para tras: Tecla 'Seta para Baixo'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*9));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
                s = "Movimentar a nave para a esquerda: Tecla 'Seta para Esquerda'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*10));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Movimentar a nave para a direita: Tecla 'Seta para Direita'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*11));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }




                s = "Zoom In: Tecla '+'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*13));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Zoom Out: Tecla '-'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*14));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }




                s = "Camara 1: Tecla 'F2'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*16));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Camara 2: Tecla 'F3'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*17));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
                s = "Camara 3: Tecla 'F4'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*18));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
                s = "Camara 4: Tecla 'F5'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*19));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }

                s = "Camara 5: Tecla 'F6'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*20));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }
                s = "Camara 6: Tecla 'F7'";
                font = GLUT_BITMAP_HELVETICA_12;
                glRasterPos2i(x + intervalo*2 , y - (intervalo*21));
                for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                {
                    char c = *i;
                    glutBitmapCharacter(font, c);
                }    
                glColor3f(1.0, 1.0, 1.0);
                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
            }

            // GLint64 timer;
            // glGetInteger64v(GL_TIMESTAMP, &timer);
            // double t = timer/1000000000.0;
            
            static long t = glutGet(GLUT_ELAPSED_TIME);
            if(ajuda||mudou_de_nivel||!world->comecou)
                stop_time = (glutGet(GLUT_ELAPSED_TIME) - t)/1000; 
            
            time_elapsed = (glutGet(GLUT_ELAPSED_TIME) - t)/1000; 
            std::string time = std::to_string(time_elapsed - stop_time);
            
            if (tempo_restante&&!ajuda&&!mudou_de_nivel&&!ganhou&&!world->perdeu&&world->comecou)
            {
                glDisable(GL_LIGHTING);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_TEXTURE_2D);
                glMatrixMode(GL_PROJECTION);
                glPushMatrix();
                glLoadIdentity();
                gluOrtho2D(0, 1000, 0, 1000);
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glLoadIdentity();
                // glBegin(GL_QUADS);
                // glColor4f(0.184314, 0.309804, 0.309804, 0.0);
                // glVertex2i(0, 50);
                // glVertex2i(0, 50);
                // glVertex2i(50, 0);
                // glVertex2i(0, 50);
                // glEnd();
                glColor3f(1.0, 1.0, 1.0);
                void *font = GLUT_BITMAP_TIMES_ROMAN_24;
                glRasterPos2i(20+glutGet(GLUT_WINDOW_WIDTH)*0.05, 900-glutGet(GLUT_WINDOW_HEIGHT)*0.02);

//******
                if(!ganhou&&!world->perdeu||world->comecou){
                    std::string s = "Tempo: "+time;
                    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
                    {
                        char c = *i;
                        glutBitmapCharacter(font, c);
                    }
                }
//******

                // glColor3f(1.0, 1.0, 1.0);
                glMatrixMode(GL_PROJECTION);
                glPopMatrix();
                glMatrixMode(GL_MODELVIEW);
                glPopMatrix();
                glEnable(GL_TEXTURE_2D);
                glEnable(GL_DEPTH_TEST);
                glEnable(GL_LIGHTING);
            }
//---------------


    glPopMatrix();

    glutSwapBuffers();
}

void init(void)

{

    win = 50;

    luzAmbiente[0] = 0.2;

    luzAmbiente[1] = 0.2;

    luzAmbiente[2] = 0.2;

    luzAmbiente[3] = 1.0;

    //GLfloat posicaoLuz[4] = {0,0,0, 1.0};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os parâmetros da luz de número 0

    //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    //glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    GLfloat luzDifusa[4] = {0.9, 0.9, 0.9, 1.0}; // "cor"

    GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"

    // Capacidade de brilho do material

    GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};

    GLint especMaterial = 10;

    // Habilita o modelo de colorização de Gouraud

    glShadeModel(GL_SMOOTH);

    // Define a refletância do material

    //glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

    // Define a concentração do brilho

    //glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
    //glMateriali(GL_FRONT, GL_DIFFUSE, especMaterial);
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, especularidade);

    // Ativa o uso da luz ambiente

    // glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // // Define os parâmetros da luz de número 0

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

    //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    //glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Habilita a definição da cor do material a partir da cor corrente

    glEnable(GL_COLOR_MATERIAL);

    //Habilita o uso de iluminação

    glEnable(GL_LIGHTING);

    // Habilita a luz de número 0

    glEnable(GL_LIGHT0);

    // Habilita o depth-buffering

    glEnable(GL_DEPTH_TEST);

    glEnable(GLUT_MULTISAMPLE);

    textura_fundo();

    DiscoNave::inicializarTextura();

    CupulaNave::inicializarTextura();

    BaseNave::inicializarTextura();

    Planeta::inicializarTextura();

    Sol::inicializarTextura();

    Satelite::inicializarTextura();

    Asteroide1::inicializarTextura();

    Asteroide2::inicializarTextura();

    Terra::inicializarTextura();

    Lua::inicializarTextura();

    Foguetao::inicializarTextura();

    world = new World();

    rot = new RotationHandler(world);

    cam = new Camera(world);

    world->setCamera(cam);

    rot->Start();

    cam->Start();

    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)

{

    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45, (float)w / h, 0.5, 600);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    cam->changeCamera();
}

void destroy()
{

    delete rot;

    delete cam;

    delete world;
}

//----------------------------------------------------

// Gerenciamento do menu com as opções de cores

void Menu_Flat_Wireframe(int op)

{

    switch (op)
    {

    case 0:

        //glLoadIdentity();

        pressed = true;

        //glLoadIdentity();

        break;

    case 1:

        //glLoadIdentity();

        pressed = false;

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

    switch (op)
    {

    case 0:

        iluminacao = true;

        break;

    case 1:

        iluminacao = false;

        break;
    }

    glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores

void GouraudShading(int op)

{

    switch (op)
    {

    case 0:

        shading = true;

        break;

    case 1:

        shading = false;

        break;
    }

    glutPostRedisplay();
}

// Gerenciamento do menu com as opções de cores

void Antialiasing(int op)

{

    switch (op)
    {

    case 0:

        antialiasing = true;

        break;

    case 1:

        antialiasing = false;

        break;
    }

    glutPostRedisplay();
}

// Criacao do Menu

void CriaMenu()

{

    int menu, submenu1, submenu2, submenu3, submenu4;

    //glLoadIdentity();

    submenu1 = glutCreateMenu(Menu_Flat_Wireframe);

    glutAddMenuEntry("Wireframe", 0);

    glutAddMenuEntry("Flat", 1);

    submenu2 = glutCreateMenu(Iluminacao);

    glutAddMenuEntry("ON", 0);

    glutAddMenuEntry("OFF", 1);

    submenu3 = glutCreateMenu(GouraudShading);

    glutAddMenuEntry("ON", 0);

    glutAddMenuEntry("OFF", 1);

    submenu4 = glutCreateMenu(Antialiasing);

    glutAddMenuEntry("ON", 0);

    glutAddMenuEntry("OFF", 1);

    menu = glutCreateMenu(MenuPrincipal);

    glutAddSubMenu("Flat ou Wireframe", submenu1);

    glutAddSubMenu("Iluminacao", submenu2);

    glutAddSubMenu("Gouraud Shading", submenu3);

    glutAddSubMenu("Antialiasing", submenu4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void GerenciaMouse(int button, int state, int x, int y)

{

    if (button == GLUT_RIGHT_BUTTON)

        if (state == GLUT_DOWN)

            CriaMenu();

    glutPostRedisplay();
}

void mainloop()
{

    static long last_time = glutGet(GLUT_ELAPSED_TIME);

    long currTime = glutGet(GLUT_ELAPSED_TIME);

    if (currTime - last_time > FRAME_DELTA)
    {
        if(!ajuda&&!mudou_de_nivel)
        world->update();

        glutPostRedisplay();

        i = 0;

        last_time = currTime;
    }

    i++;
}

int main(int argc, char **argv)

{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);

    glutInitWindowSize(750, 700);

    glutInitWindowPosition(550, 250);

    Window = glutCreateWindow(argv[0]);

    glutReshapeFunc(reshape);



    glutDisplayFunc(display);

    glewInit();

    init();
    
    int iMultiSample, iNumSample;

    glGetIntegerv(GL_SAMPLE_BUFFERS, &iMultiSample);

    glGetIntegerv(GL_SAMPLES, &iNumSample);

    glutMouseFunc(GerenciaMouse);

    glutSpecialFunc(keyboardHandler);

    glutKeyboardFunc(teclas);
    
    glutTimerFunc(30000, Timer, 1);

    glutIdleFunc(mainloop);

    glutMainLoop();

    destroy();

    return 0;
}