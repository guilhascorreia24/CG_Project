// Menu.c - Isabel H. Manssour
// Um programa OpenGL simples que exemplifica
// como exibir textos e utilizar menus e funções 
// callback para verificar a movimentação do 
// mouse na janela GLUT.
// Este código está baseado nos exemplos 
// disponíveis no livro "OpenGL SuperBible", 
// 2nd Edition, de Richard S. e Wright Jr.

#include "utils.h"

// Constantes
#define ON_IL 0
#define OFF_IL 1

#define ON_GR 2
#define OFF_GR 3

#define ON_ANTI 4
#define OFF_ANTI 5

// Variáveis
char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, primitiva;

void DesenhaIl(bool s)
{

}

void DesenhaGR(bool s)
{

}

void DesenhaAN(bool s)
{

}

// Desenha um texto na janela GLUT
void DesenhaTexto(char *string) 
{  
  	glPushMatrix();
        // Posição no universo onde o texto será colocado          
        glRasterPos2f(-win,win-(win*0.08)); 
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	glPopMatrix();
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
                   
     glClear(GL_COLOR_BUFFER_BIT);
     
     // Define a cor corrente
     glColor3f(r,g,b);

     // Desenha uma primitiva     
     switch (primitiva) {
            case ON_IL:  DesenhaIl(TRUE);
                            break;
            case OFF_IL:  DesenhaIl(FALSE);
                            break;
            case ON_GR:   DesenhaGR(TRUE);                       
                            break;
            case OFF_GR:   DesenhaGR(FALSE);                       
                            break;
            case ON_ANTI:   DesenhaAN(TRUE);                       
                            break;
            case OFF_ANTI:   DesenhaAN(FALSE);                       
                            break;
     }

     // Exibe a posição do mouse na janela
     glColor3f(1.0f,1.0f,1.0f);
     DesenhaTexto(texto);
     
     glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    win=150.0f;
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    // Especifica as dimensões da Viewport
    glViewport(0, 0, w, h);
    view_w = w;
    view_h = h;                   

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT com um botão pressionado
void MoveMouseBotaoPressionado(int x, int y)
{
     sprintf(texto, "Botao pressionado (%d,%d)", x, y);
     //glutPostRedisplay()();
}

// Função callback chamada sempre que o mouse é movimentado
// sobre a janela GLUT 
void MoveMouse(int x, int y)
{
     sprintf(texto, "(%d,%d)", x, y);
     //glutPostRedisplay()();
}

// Função callback chamada para gerenciar eventos do teclado   
// para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           win -= 10;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    if(key == GLUT_KEY_DOWN) {
           win += 10;
           if (win > 500) win = 500;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    //glutPostRedisplay()();
}
           

// Gerenciamento do menu iluminacao        
void Menu_Iluminacao(int op)
{
   switch(op) {
            case 0:
                     r = 1.0f;
                     g = 0.0f;
                     b = 0.0f;
                     break;
            case 1:
                     r = 0.0f;
                     g = 1.0f;
                     b = 0.0f;
                     break;
    }
    //glutPostRedisplay()();
}           

// Gerenciamento do menu iluminacao        
void Menu_Gouraud(int op)
{
   switch(op) {
            case 0:
                     r = 1.0f;
                     g = 0.0f;
                     b = 0.0f;
                     break;
            case 1:
                     r = 0.0f;
                     g = 1.0f;
                     b = 0.0f;
                     break;
    }
    //glutPostRedisplay()();
}           

// Gerenciamento do menu iluminacao        
void Menu_Antialiasing(int op)
{
   switch(op) {
            case 0:
                     r = 1.0f;
                     g = 0.0f;
                     b = 0.0f;
                     break;
            case 1:
                     r = 0.0f;
                     g = 1.0f;
                     b = 0.0f;
                     break;
    }
    //glutPostRedisplay()();
}           
 
        
// Gerenciamento do menu principal           
void MenuPrincipal(int op)
{
}
              
// Criacao do Menu
void CriaMenu() 
{
    int menu,submenu1,submenu2, submenu3;

	submenu1 = glutCreateMenu(Menu_Iluminacao);
	glutAddMenuEntry("On",0);
	glutAddMenuEntry("Off",1);
    

    submenu2 = glutCreateMenu(Menu_Gouraud);
	glutAddMenuEntry("On",3);
	glutAddMenuEntry("Off",4);

    submenu3 = glutCreateMenu(Menu_Antialiasing);
	glutAddMenuEntry("On",5);
	glutAddMenuEntry("Off",6);

    menu = glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Iluminacao",submenu1);
	glutAddSubMenu("Gouraud Shading",submenu2);
	glutAddSubMenu("Antialiasing",submenu3);
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
           
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
            CriaMenu();
         
    //glutPostRedisplay()();
}



                      
// Programa Principal 
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
     glutInitWindowSize(350,300);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Exemplo de Menu e Exibição de Caracteres");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutMotionFunc(MoveMouseBotaoPressionado); 
     glutPassiveMotionFunc(MoveMouse);
     glutMouseFunc(GerenciaMouse);    
     glutSpecialFunc(TeclasEspeciais); 
     Inicializa();
     glutMainLoop();
}