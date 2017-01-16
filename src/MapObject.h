//
// Created by adrien on 1/13/17.
//

#ifndef EXECUTABLE_MAPOBJECT_H
#define EXECUTABLE_MAPOBJECT_H


#include "GameObject.h"
#include "Model.h"
#include "GameData.h"

//FINI

class MapObject : public GameObject{
public:
    MapObject(int type, char *modelpath, char *texturepath, GLuint shader_program_id, vec3 p_pos, vec3 p_orientation) ;
    MapObject(int type, Model *p_model, vec3 p_pos, vec3 p_orientation);
    void update(double dt, Data *gdata);
    void draw();

private:
    Model *model;

    int type;
};


#endif //EXECUTABLE_MAPOBJECT_H
