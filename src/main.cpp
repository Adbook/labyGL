/*****************************************************************************\
 * TP CPE, 3ETI, TP synthese d'images
 * --------------
 *
 * Programme principal des appels OpenGL
\*****************************************************************************/
#define SCREEN_W 1600
#define SCREEN_H 900


#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>

#include "glutils.hpp"

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "mesh.hpp"
#include "KeyboardHandler.h"
#include "GameState.h"
#include <ctime>

bool mouse_button_down = false;


#define toRad(degrees) (degrees * M_PI / 180.0f)

GameState gameState;

static void init()
{

    glEnable(GL_DEPTH_TEST); PRINT_OPENGL_ERROR();
}

static void display_callback()
{
    gameState.draw();
}

static void timer_callback(int)
{
    glutTimerFunc(25, timer_callback, 0);
    gameState.update();
}

void mouse_motion_callback(int x, int y)
{
    gameState.gdata.mouse_x = x;
    gameState.gdata.mouse_y = y;

}
void mouse_callback(int button, int state, int x, int y)
{

    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        mouse_button_down = true;
    }
    else mouse_button_down = false;
}

void handle_glut_key_down(unsigned char key, int x, int y)
{
    gameState.gdata.kbrd.handle_glut_key_down(key, x, y);
}

void handle_glut_key_up(unsigned char key, int x, int y)
{
    gameState.gdata.kbrd.handle_glut_key_up(key, x, y);
}

int main(int argc, char** argv)
{
    srand(time(0));

    //**********************************************//
    //Lancement des fonctions principales de GLUT
    //**********************************************//

    //initialisation
    glutInit(&argc, argv);

    //Mode d'affichage (couleur, gestion de profondeur, ...)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    //Taille de la fenetre a l'ouverture
    glutInitWindowSize(SCREEN_W, SCREEN_H);

    //Titre de la fenetre
    glutCreateWindow("OpenGL");

    //Fonction de la boucle d'affichage
    glutDisplayFunc(display_callback);
    glutSetCursor(GLUT_CURSOR_NONE);
    //Fonction de gestion du clavier
    glutKeyboardFunc(handle_glut_key_down);
    glutKeyboardUpFunc(handle_glut_key_up);
    glutMouseFunc(mouse_callback);
    glutPassiveMotionFunc(mouse_motion_callback);
    //Fonction des touches speciales du clavier (fleches directionnelles)


    //Fonction d'appel d'affichage en chaine
    glutTimerFunc(25, timer_callback, 0);

    //Initialisation des fonctions OpenGL
    glewInit();

    //Notre fonction d'initialisation des donnees et chargement des shaders
    init();

    gameState.onEnter();

    glutMainLoop();

    //Plus rien n'est execute apres cela

    return 0;
}


