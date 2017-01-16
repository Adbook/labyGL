//
// Created by adrien on 1/9/17.
//


#include "View.h"


vec3 View::getCenter() {
    return m_center;
}

vec3 View::getRotation() {
    return m_rotation;
}

void View::rotate(float x, float y, float z) {
    m_rotation.x += x;
    m_rotation.y += y;
    m_rotation.z += z;

    //modulo:

    while(m_rotation.x > 2*M_PI){
        m_rotation.x -= 2*M_PI;
    }
    while(m_rotation.y > 2*M_PI){
        m_rotation.y -= 2*M_PI;
    }
    while(m_rotation.z > 2*M_PI){
        m_rotation.z -= 2*M_PI;
    }
}

void View::translate(float x, float y, float z) {
    m_center.x += x;
    m_center.y += y;
    m_center.z += z;
}

void View::setCenter(float x, float y, float z) {
    m_center.x = x;
    m_center.y = y;
    m_center.z = z;
}

void View::setRotation(float x, float y, float z) {
    m_rotation.x = x;
    m_rotation.y = y;
    m_rotation.z = z;

    while(m_rotation.x > 2*M_PI){
        m_rotation.x -= 2*M_PI;
    }
    while(m_rotation.y > 2*M_PI){
        m_rotation.y -= 2*M_PI;
    }
    while(m_rotation.z > 2*M_PI){
        m_rotation.z -= 2*M_PI;
    }
}

mat4 View::getRotationMatrix() {
    return matrice_rotation(m_rotation.x, 1.0,0.0,0.0) * matrice_rotation(m_rotation.y, 0.0, 1.0, 0.0) * matrice_rotation(m_rotation.z, 0.0, 0.0, 1.0);
}