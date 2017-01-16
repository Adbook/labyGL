//
// Created by adrien on 12/18/16.
//

#include "Model.h"


void Model::load(char *model_path, char *texture_path, float s)  {
    // Chargement d'un maillage a partir d'un fichier
    mesh m = load_obj_file(model_path);

    // Affecte une transformation sur les sommets du maillage

    mat4 transform = mat4(   s, 0.0f, 0.0f, 0.0f,
                             0.0f,    s, 0.0f,-0.9f,
                             0.0f, 0.0f,   s ,-2.0f,
                             0.0f, 0.0f, 0.0f, 1.0f);
    apply_deformation(&m,transform);

    // Centre la rotation du modele 1 autour de son centre de gravite approximatif
    m_transform.rotation_center = vec3(s/2.f,s/2.f,s/2.f);

    // Calcul automatique des normales du maillage
    update_normals(&m);
    // Les sommets sont affectes a une couleur blanche
    fill_color(&m,vec3(1.0f,1.0f,1.0f));

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&m_vbo); PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo); PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER,m.vertex.size()*sizeof(vertex_opengl),&m.vertex[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&m_vboi); PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_vboi); PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,m.connectivity.size()*sizeof(triangle_index),&m.connectivity[0],GL_STATIC_DRAW); PRINT_OPENGL_ERROR();

    // Nombre de triangles de l'objet 1
    m_nbr_triangle = m.connectivity.size();

    // Chargement de la texture
    load_texture(texture_path,&m_texture_id);
    setScale(s, s, s);
}

void Model::draw(){

    //envoie des parametres uniformes
    {
        glUniformMatrix4fv(get_uni_loc(m_shader_id,"rotation_model"),1,false,pointeur(m_transform.rotation));    PRINT_OPENGL_ERROR();

        vec3 c = m_transform.rotation_center;
        glUniform4f(get_uni_loc(m_shader_id,"rotation_center_model") , c.x,c.y,c.z , 0.0f);                                 PRINT_OPENGL_ERROR();

        vec3 t = m_transform.translation;
        glUniform4f(get_uni_loc(m_shader_id,"translation_model") , t.x,t.y,t.z , 0.0f);                                     PRINT_OPENGL_ERROR();

    //    glUniform4f(get_uni_loc(m_shader_id,"scaling"), m_scale_x, m_scale_y, m_scale_z, 0.0f);                             PRINT_OPENGL_ERROR();
    }

    //placement des VBO
    {

        //selection du VBO courant
        glBindBuffer(GL_ARRAY_BUFFER,m_vbo);                                                    PRINT_OPENGL_ERROR();

        // mise en place des differents pointeurs
        glEnableClientState(GL_VERTEX_ARRAY);                                                          PRINT_OPENGL_ERROR();
        glVertexPointer(3, GL_FLOAT, sizeof(vertex_opengl), 0);                                        PRINT_OPENGL_ERROR();

        glEnableClientState(GL_NORMAL_ARRAY); PRINT_OPENGL_ERROR();                                    PRINT_OPENGL_ERROR();
        glNormalPointer(GL_FLOAT, sizeof(vertex_opengl), buffer_offset(sizeof(vec3)));                 PRINT_OPENGL_ERROR();

        glEnableClientState(GL_COLOR_ARRAY); PRINT_OPENGL_ERROR();                                     PRINT_OPENGL_ERROR();
        glColorPointer(3,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(2*sizeof(vec3)));              PRINT_OPENGL_ERROR();

        glEnableClientState(GL_TEXTURE_COORD_ARRAY); PRINT_OPENGL_ERROR();                             PRINT_OPENGL_ERROR();
        glTexCoordPointer(2,GL_FLOAT, sizeof(vertex_opengl), buffer_offset(3*sizeof(vec3)));           PRINT_OPENGL_ERROR();

    }
    glScalef(m_scale_x, m_scale_y, m_scale_z);
    //affichage
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_vboi);                           PRINT_OPENGL_ERROR();
        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glPointSize(5.0);

       // glDrawArrays(GL_POINTS, 0, 3);

       // glDrawArrays(GL_LINE_LOOP, 0, 3);
        PRINT_OPENGL_ERROR();
        //glDrawElements(GL_LINE_LOOP, 3*m_nbr_triangle, GL_UNSIGNED_INT, 0);     PRINT_OPENGL_ERROR();
        glDrawElements(GL_TRIANGLES, 3*m_nbr_triangle, GL_UNSIGNED_INT, 0);
    }

    glScalef(1/m_scale_x, 1/m_scale_y, 1/m_scale_z);
}

void Model::translate(float x, float y, float z){
    m_transform.translation.x += x;
    m_transform.translation.y += y;
    m_transform.translation.z += z;
}
void Model::translateTo(float x, float y, float z){
    m_transform.translation.x = x;
    m_transform.translation.y = y;
    m_transform.translation.z = z;
}

void Model::rotate(float rx, float ry, float rz){
    m_angle_x += rx;
    m_angle_y += ry;
    m_angle_z += rz;
    m_transform.rotation = matrice_rotation(m_angle_y , 0.0f,1.0f,0.0f) * matrice_rotation(m_angle_x , 1.0f,0.0f,0.0f);
}
void Model::setRotation(float rx, float ry, float rz){
    m_angle_x = rx;
    m_angle_y = ry;
    m_angle_z = rz;
    m_transform.rotation = matrice_rotation(m_angle_y , 0.0f,1.0f,0.0f) * matrice_rotation(m_angle_x , 1.0f,0.0f,0.0f);
}


void Model::load_texture(const char* filename,GLuint *texture_id)
{
    // Chargement d'une texture (seul les textures tga sont supportes)
    Image  *image = image_load_tga(filename);
    if (image) //verification que l'image est bien chargee
    {

        //Creation d'un identifiant pour la texture
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); PRINT_OPENGL_ERROR();
        glGenTextures(1, texture_id); PRINT_OPENGL_ERROR();

        //Selection de la texture courante a partir de son identifiant
        glBindTexture(GL_TEXTURE_2D, *texture_id); PRINT_OPENGL_ERROR();

        //Parametres de la texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); PRINT_OPENGL_ERROR();

        //Envoie de l'image en memoire video
        if(image->type==IMAGE_TYPE_RGB){ //image RGB
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->data); PRINT_OPENGL_ERROR();}
        else if(image->type==IMAGE_TYPE_RGBA){ //image RGBA
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width, image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data); PRINT_OPENGL_ERROR();}
        else{
            std::cout<<"Image type not handled"<<std::endl;}

        delete image;
    }
    else
    {
        std::cerr<<"Erreur chargement de l'image, etes-vous dans le bon repertoire?"<<std::endl;
        abort();
    }

    glUniform1i (get_uni_loc(m_shader_id, "texture"), 0); PRINT_OPENGL_ERROR();


}

std::string Model::to_string() {
    std::string mess = "Modele ";
    mess += this->m_nbr_triangle;
    std::cout << m_nbr_triangle << std::endl;
    return mess;
}

void Model::setScale(float sx, float sy, float sz) {
    m_scale_x = sx;
    m_scale_y = sy;
    m_scale_z = sz;
}
