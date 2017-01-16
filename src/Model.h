//
// Created by adrien on 12/18/16.
//

#ifndef EXECUTABLE_MODEL_H
#define EXECUTABLE_MODEL_H

#include <GL/glew.h>
#include <GL/glut.h>

#include "glutils.hpp"

#include "mat4.hpp"
#include "vec3.hpp"
#include "vec2.hpp"
#include "triangle_index.hpp"
#include "vertex_opengl.hpp"
#include "image.hpp"
#include "mesh.hpp"
#include <string.h>

//Matrice de transformation
struct transformation
{
    mat4 rotation;
    vec3 rotation_center;
    vec3 translation;

    transformation():rotation(),rotation_center(),translation(){}
};

class Model{
public:
    void load(char *model_path, char *texture_path, float s);

    void set_shader_id(GLuint shader_id)
    {
        m_shader_id = shader_id;
    }
    void draw();

    void translate(float x, float y, float z);
    void translateTo(float x, float y, float z);
    void rotate(float rx, float ry, float rz);
    void setRotation(float rx, float ry, float rz);
    void setScale(float sx, float sy, float sz);
    void load_texture(const char* filename,GLuint *texture_id);
    std::string to_string();

protected:
    GLuint m_vbo;
    GLuint m_vboi;
    GLuint m_texture_id;
    GLuint m_shader_id;

    int m_nbr_triangle;

    float m_angle_x;
    float m_angle_y;
    float m_angle_z;

    float m_scale_x;
    float m_scale_y;
    float m_scale_z;

    transformation m_transform;

};

#endif //EXECUTABLE_MODEL_H
