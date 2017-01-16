//
// Created by adrien on 1/13/17.
//

#ifndef EXECUTABLE_GAMEDATA_H
#define EXECUTABLE_GAMEDATA_H


#include <vector>
#include "View.h"
#include "GameObject.h"
#include "Player.h"
#include "KeyboardHandler.h"
#include <iostream>
#include <GL/glew.h>

class GameData : public Data{
public:
//pas le temps de faire tous les accesseurs
    GameData();
    View camera;

    GameObject* gameObjects[2048];
    int nbGameObjects;
    Player player;

    int mouse_x;
    int mouse_y;

    KeyboardHandler kbrd;

    int mapSize;
    int * map;

    GLuint shader_program_id;


    bool perso_saute = false;
    float perso_dy = 0;
    float perso_dx = 0;
    float perso_ax = 0;


    void addGameObject(GameObject *obj);
    GameObject *getGameObjectById(int i);
    GameObject *getGameObjectByIndex(int index);
private:

};


#endif //EXECUTABLE_GAMEDATA_H
