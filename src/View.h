//
// Created by adrien on 1/9/17.
//

#ifndef EXECUTABLE_VIEW_H
#define EXECUTABLE_VIEW_H


#include "vec3.hpp"
#include "mat4.hpp"
#include <math.h>

class View {

public:
    vec3 getCenter();
    vec3 getRotation();

    mat4 getRotationMatrix();
    void translate(float x, float y, float z);
    void rotate(float x, float y, float z);

    void setCenter(float x, float y, float z);
    void setRotation(float x, float y, float z);

private:
    vec3 m_center;
    vec3 m_rotation;
};


#endif //EXECUTABLE_VIEW_H
