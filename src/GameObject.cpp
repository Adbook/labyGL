//
// Created by adrien on 1/13/17.
//

#include "GameObject.h"

GameObject::GameObject(vec3 p_pos, vec3 p_orientation) {
    position = p_pos;
    orientation = p_orientation;
}

GameObject::GameObject() {

}





vec3 GameObject::getPosition() {
    return position;
}

vec3 GameObject::getRotation() {
    return orientation;
}

void GameObject::translateTo(vec3 pos) {
    position = pos;
}

void GameObject::translate(vec3 v) {
    position.x += v.x;
    position.y += v.y;
    position.z += v.z;

}

void GameObject::rotateTo(vec3 rot) {
    orientation = rot;
}

void GameObject::rotate(vec3 ang) {
    orientation.x += ang.x;
    orientation.y += ang.y;
    orientation.z += ang.z;
}

