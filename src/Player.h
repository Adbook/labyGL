//
// Created by adrien on 1/13/17.
//
//
#ifndef EXECUTABLE_PLAYER_H
#define EXECUTABLE_PLAYER_H

//#include "GameData.h
#include "GameObject.h"
#include "Data.h"
#include <GL/glew.h>
#include <GL/glut.h>
class Player : public GameObject{
public:
    void update(double dt, Data *gdata);
    void draw();

private:
    bool saute;
    vec3 v;
};


#endif //EXECUTABLE_PLAYER_H
