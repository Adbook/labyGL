//
// Created by adrien on 1/13/17.
//

#include "MapObject.h"

MapObject::MapObject(int p_type, Model *p_model, vec3 p_pos, vec3 p_orientation) {
    type = p_type;
    position = p_pos;
    orientation = p_orientation;
    model = p_model;
}

MapObject::MapObject(int p_type, char *modelpath, char *texturepath, GLuint shader_program_id, vec3 p_pos,
                     vec3 p_orientation) {
    type = p_type;
    position = p_pos;
    orientation = p_orientation;

    model = new Model();
    model->load(modelpath, texturepath, 0.9f);
    model->set_shader_id(shader_program_id);
    model->translate(p_pos.x,p_pos.y,p_pos.z);
    model->rotate(p_orientation.x, p_orientation.y, p_orientation.z);

}



void MapObject::update(double dt, Data *gdata) {
    std::cout << "type" << type << std::endl;
    if(type == 1) {
       // translate(vec3(((double) rand() / (RAND_MAX)) - 0.5, 0, ((double) rand() / (RAND_MAX)) - 0.5));
    }
    //rotate(vec3(rand()/100, rand()/100, rand()/100));
    std::cout << orientation.y << std::endl;
    // rien à faire dans ce cas ?
}

void MapObject::draw() {
    model->translateTo(position.x, position.y, position.z);
    model->setRotation(orientation.x, orientation.y, orientation.z);
    model->draw();
}


