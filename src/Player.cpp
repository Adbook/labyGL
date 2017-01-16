//
// Created by adrien on 1/13/17.
//

#include "Player.h"
#include "GameData.h"
#define SCREEN_W 1600
#define SCREEN_H 900
void Player::update(double dt, Data *data) {
    GameData gdata = *(GameData*)data;

    float angle_view_z = 0.0f;
    float angle_view_x = 0.0f;
    float angle_view_y = 0.0f;

    float speed_factor = 0.3;

    const vec3 rot =gdata.camera.getRotation();
    const vec3 center =gdata.camera.getCenter();

    float sinXRot = -sinf( ( orientation.x ) ) * speed_factor;
    float cosXRot = cosf( ( orientation.x ) ) * speed_factor;

    float sinYRot = sinf( ( orientation.y ) ) * speed_factor;
    float cosYRot = cosf( ( orientation.y ) ) * speed_factor;

    float pitchLimitFactor = cosXRot;

    float nx = 0;
    float nz = 0;


    if(gdata.kbrd.is_key_down('z') ){
        nx = (position.x + sinYRot * pitchLimitFactor);
        nz = (position.z -cosYRot * pitchLimitFactor);
        if(gdata.map[(int)nx + (int)nz*gdata.mapSize] == 0 || gdata.kbrd.is_key_down('a')) {
            translate(vec3((sinYRot * pitchLimitFactor), 0, (-cosYRot * pitchLimitFactor)));
        }
    }
    if(gdata.kbrd.is_key_down('s')){
        nx = (position.x + (-sinYRot * pitchLimitFactor));
        nz = (position.z - (cosYRot * pitchLimitFactor));

        if(gdata.map[(int)nx + (int)nz*gdata.mapSize] == 0 ||gdata.kbrd.is_key_down('a')) {
            translate(vec3((-sinYRot * pitchLimitFactor), 0, (cosYRot * pitchLimitFactor)));
        }

    }
    if(gdata.kbrd.is_key_down('q')){
        nx = (position.x - cosYRot * pitchLimitFactor);
        nz = (position.z - sinYRot * pitchLimitFactor);

        if(gdata.map[(int)nx + (int)nz*gdata.mapSize] == 0 ||gdata.kbrd.is_key_down('a')) {
            std::cout << "collision\n" << std::endl;
            translate(vec3((-cosYRot) * pitchLimitFactor, 0, (-sinYRot) * pitchLimitFactor));
        }
    }
    if(gdata.kbrd.is_key_down('d')){
        nx = (position.x + (cosYRot) * pitchLimitFactor);
        nz = (position.z + (sinYRot) * pitchLimitFactor);

        if(gdata.map[(int)nx + (int)nz*gdata.mapSize] == 0 ||gdata.kbrd.is_key_down('a')) {
            translate(vec3((cosYRot) * pitchLimitFactor, 0, (sinYRot) * pitchLimitFactor));
        }
    }

    if(gdata.kbrd.is_key_down(' ') && !saute){
        saute = true;
        v.y = 0.09;
    }

    if(saute)
    {
        //if(perso_dy >= 0)
        if(!gdata.kbrd.is_key_down('a'))
            translate(vec3(0, v.y, 0));

            v.y -= 0.01;

        if(position.y <= 0.51 ) {
            v.y = 0;
            saute = false;
        }
    }

    float dx =gdata.mouse_x - SCREEN_W/2;
    float dy =gdata.mouse_y - SCREEN_H/2;
    dy = 0;

    angle_view_y = (float)dx/500.0f;
    rotate(vec3(angle_view_x, angle_view_y, angle_view_z));

}

void Player::draw() {

}
