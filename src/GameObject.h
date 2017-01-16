//
// Created by adrien on 1/13/17.
//

#ifndef EXECUTABLE_GAMEOBJECT_H
#define EXECUTABLE_GAMEOBJECT_H

#include "vec3.hpp"
#include "Data.h"

//FINI
class GameObject {
public:
    GameObject();
    GameObject(vec3 p_pos, vec3 p_orientation);
    virtual void update(double dt, Data *data) = 0;
    virtual void draw() = 0;

    vec3 getPosition();
    vec3 getRotation();

    void translateTo(vec3 pos);
    void translate(vec3 v);

    void rotateTo(vec3 rot);
    void rotate(vec3 ang);

protected:

    vec3 position;
    vec3 orientation;

};


#endif //EXECUTABLE_GAMEOBJECT_H
