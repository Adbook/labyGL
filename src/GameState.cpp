//
// Created by adrien on 1/13/17.
//

#include <cstdlib>
#include "GameState.h"
#include "MapObject.h"
#include "GroundModel.h"

void GameState::generateMaze(int tailleCarte, int *map)
{
    //déclaration de la carte
    int taille=(tailleCarte-1)/2;
    for (int j=0;j<tailleCarte;++j)
    {
        for (int i=0;i<tailleCarte;++i)
        {
            map[i+j*tailleCarte]=1;
        }
    }

    // déclaration des poids + création cellule
    int poids[taille*taille];
    for(int j=0;j<taille;j++)
    {
        for(int i=0;i<taille;i++)
        {
            poids[i+j*taille]=i+taille*j+1;
            map[(2*i+1)+(2*j+1)*tailleCarte]=0;
        }
    }
    int h=0;
    while(h<taille*taille-1)
    {
        int x=rand()%taille;
        int y=rand()%taille;
        int boussole=rand()%4;
        int Xmove=0,Ymove=0;
        switch(boussole)
        {
            case 0:
                Xmove=x+1;Ymove=y;
                break;
            case 1:
                Xmove=x-1;Ymove=y;
                break;
            case 2:
                Ymove=y+1;Xmove=x;
                break;
            case 3:
                Ymove=y-1;Xmove=x;
                break;
        }
        if(!(Xmove<0 || Xmove>=taille || Ymove<0 || Ymove>=taille))
        {
            //Si poids différent on change
            if(poids[x+y*taille]!=poids[Xmove+Ymove*taille])
            {
                int temp=poids[Xmove+Ymove*taille];
                for(int j=0;j<taille;j++)
                {
                    for(int i=0;i<taille;i++)
                    {
                        if(poids[i+j*taille]==temp)
                        {
                            poids[i+j*taille]=poids[x+y*taille];
                        }
                    }
                }
                std::cout << 2*x+2 << " "<< (2*y+1)*tailleCarte << std::endl;
                switch(boussole)
                {

                    case 0:
                        map[(2*x+2)+(2*y+1)*tailleCarte]=0;
                        break;
                    case 1:
                        map[(2*x)+(2*y+1)*tailleCarte]=0;
                        break;
                    case 2:
                        map[(2*x+1)+(2*y+2)*tailleCarte]=0;
                        break;
                    case 3:
                        map[(2*x+1)+(2*y)*tailleCarte]=0;
                        break;
                }
                h++;
            }
        }
    }

}


void GameState::draw(){
    glClearColor(0.5f, 0.6f, 0.9f, 1.0f);                 PRINT_OPENGL_ERROR();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   PRINT_OPENGL_ERROR();

    // Affecte les parametres uniformes de la vue (identique pour tous les modeles de la scene)
    {

        //envoie de la rotation
        glUniformMatrix4fv(get_uni_loc(gdata.shader_program_id,"rotation_view"),1,false,pointeur(gdata.camera.getRotationMatrix())); PRINT_OPENGL_ERROR();

        //envoie du centre de rotation
        vec3 cv = gdata.camera.getCenter();
        //vec3 tv = transformation_view.translation;
        // test1.translateTo(cv.x, cv.y ,cv.z);
        glUniform4f(get_uni_loc(gdata.shader_program_id,"rotation_center_view") , cv.x, cv.y, cv.z, 0.0f); PRINT_OPENGL_ERROR();

        //envoito rardededededde de la translation
        glUniform4f(get_uni_loc(gdata.shader_program_id,"translation_view") ,- cv.x,-cv.y,-cv.z , 0.0f); PRINT_OPENGL_ERROR();
    }

    for(int i = 0; i< gdata.nbGameObjects; i++)
    {
       // std::cout << "draw " << i << std::endl;
        gdata.getGameObjectByIndex(i)->draw();
    }

    glutSwapBuffers();
}

void GameState::onLeave(){

}

void GameState::onEnter(){
    gdata.shader_program_id = read_shader("shader.vert", "shader.frag");

    mat4 projection = matrice_projection(60.0f*M_PI/180.0f,1.0f,0.01f,1000.0f);
    glUniformMatrix4fv(get_uni_loc(gdata.shader_program_id,"projection"),1,false,pointeur(projection)); PRINT_OPENGL_ERROR();

    gdata.mapSize = 25;
    gdata.map = (int*)malloc(sizeof(int)*gdata.mapSize*gdata.mapSize);
    generateMaze(25, gdata.map);
    for(int i = 0; i < 25*25; i++)
    {
        std::cout << gdata.map[i]<< std::endl;
    }

    Model *box1 = new Model;
    float cubesize = 0.5f;
    box1->load("../data/untitled.obj", "../data/cabinet.tga", cubesize);
    box1->setScale(0.1f, 0.1f, 0.1f);
    box1->set_shader_id(gdata.shader_program_id);
    box1->translate(-20.0,1.0,1.0);

    for(int i = 0; i < gdata.mapSize; i++)
    {
        for(int j = 0; j < gdata.mapSize; j++)
        {
            if(gdata.map[j + i * gdata.mapSize])
            gdata.addGameObject(new MapObject(1, box1, vec3(j+cubesize, 1+cubesize, i+cubesize), vec3(0, 0, 0)));
        }
    }

    GroundModel *ground = new GroundModel;
    ground->set_shader_id(gdata.shader_program_id);
    ground->load();
    gdata.addGameObject(new MapObject(2, ground, vec3(0,0,0), vec3(0,0,0)));
    gdata.addGameObject(new MapObject(2, ground, vec3(0,1,0), vec3(0,0,0)));
}


void GameState::update() {

    gdata.player.update(0, &gdata);
    gdata.camera.setCenter(gdata.player.getPosition().x, gdata.player.getPosition().y, gdata.player.getPosition().z);
    gdata.camera.setRotation(gdata.player.getRotation().x, gdata.player.getRotation().y, gdata.player.getRotation().z);

    for(int i = 0; i < gdata.nbGameObjects; i++)
    {
        gdata.getGameObjectByIndex(i)->update(0, &gdata);
    }
    glutWarpPointer(SCREEN_W/2, SCREEN_H/2);
    glutPostRedisplay();
}
