//
// Created by adrien on 12/18/16.
//

#include "LabyModel.h"
/*****************************
 *

 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */


void LabyModel::load(int taille, int *map) {
    /*int lv_w = 45;
    int lv_h = 17;
    int map[] = {
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
            1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,
            1,0,0,0,1,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,
            1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
            1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
            1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
            1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,
            1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
            1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,
            1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
            1,0,0,0,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1,
            1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    };*/
    int lv_w = taille;
    int lv_h = taille;

    std::vector<vertex_opengl> vertices;
    std::vector<triangle_index> triangles;

    unsigned int index = 0;

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

//    for(int x = -25; x < 25; x+=1)
    for(int i = 0; i < lv_w; i ++)
    {
        int y=0;
        //for(int y = -25; y < 25; y+=1)

        {

//            for(int z = -25; z < 25; z+=1)
            for(int j = 0; j < lv_h; j++)
            {
                int x = i;
                int z = j;
                std:: cout << x << " " << y << " " << z << std::endl;

                if(map[j * lv_w + i] == 1)
                {
                    /*vec3 p0 = vec3(x - 0.5f, y + 0.5f, z + 0.5f);
                    vec3 p1 = vec3(x - 0.5f, y - 0.5f, z + 0.5f);
                    vec3 p2 = vec3(x + 0.5f, y - 0.5f, z + 0.5f);
                    vec3 p3 = vec3(x + 0.5f, y + 0.5f, z + 0.5f);

                    vec3 p4 = vec3(x - 0.5f, y + 0.5f, z - 0.5f);
                    vec3 p5 = vec3(x - 0.5f, y - 0.5f, z - 0.5f);
                    vec3 p6 = vec3(x + 0.5f, y - 0.5f, z - 0.5f);
                    vec3 p7 = vec3(x + 0.5f, y + 0.5f, z - 0.5f);*/

                    vec3 p0 = vec3(x, y + 1, z + 1);
                    vec3 p1 = vec3(x, y, z + 1);
                    vec3 p2 = vec3(x + 1, y, z + 1);
                    vec3 p3 = vec3(x + 1, y + 1, z + 1);

                    vec3 p4 = vec3(x , y + 1, z );
                    vec3 p5 = vec3(x , y , z );
                    vec3 p6 = vec3(x + 1, y , z );
                    vec3 p7 = vec3(x + 1, y + 1, z );

                    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
                    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
                    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
                    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);

                    vertex_opengl v4=vertex_opengl(p4,n0,c0,t0);
                    vertex_opengl v5=vertex_opengl(p5,n1,c1,t1);
                    vertex_opengl v6=vertex_opengl(p6,n2,c2,t2);
                    vertex_opengl v7=vertex_opengl(p7,n3,c3,t3);

                    //TEST
                    vertex_opengl v8=vertex_opengl(p1,n0,c0,t0);
                    vertex_opengl v9=vertex_opengl(p5,n1,c1,t1);
                    vertex_opengl v10=vertex_opengl(p6,n2,c2,t2);
                    vertex_opengl v11=vertex_opengl(p2,n3,c3,t3);
                    /*
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);

                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);

                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    vertex_opengl v8=vertex_opengl(p,n,c,t);
                    */


                    /***        1
*                          v5  --------- v6           0---- x
*                         /  |         /             / |
*                     v1  ----------v2  |           z  |
*                         |  |      | 2 | v7           y
*                      4  |  v4___  |  /
*                         |         |/
*                      v0  ---------  v3
 *                             3        **/

                    triangle_index tr0 = triangle_index(index + 0, index + 1, index + 3);
                    triangle_index tr1 = triangle_index(index + 1, index + 2, index + 3);

                    triangle_index tr2 = triangle_index(index + 1, index + 5, index + 2);
                    triangle_index tr3 = triangle_index(index + 2, index + 5, index + 6);

                    triangle_index tr4 = triangle_index(index + 3, index + 2, index + 6);
                    triangle_index tr5 = triangle_index(index + 3, index + 7, index + 6);

                    triangle_index tr6 = triangle_index(index + 4, index + 7, index + 5);
                    triangle_index tr7 = triangle_index(index + 7, index + 5, index + 6);

                    triangle_index tr8 = triangle_index(index + 0, index + 4, index + 3);
                    triangle_index tr9 = triangle_index(index + 3, index + 4, index + 7);

                    triangle_index tr10 = triangle_index(index + 0, index + 1, index + 5);
                    triangle_index tr11 = triangle_index(index + 0, index + 4, index + 5);

                    //test
                    triangle_index tr12 = triangle_index(index + 8, index + 11, index + 10);
                    triangle_index tr13 = triangle_index(index + 9, index + 10, index + 11);

                    vertices.push_back(v0);
                    vertices.push_back(v1);
                    vertices.push_back(v2);
                    vertices.push_back(v3);

                    vertices.push_back(v4);
                    vertices.push_back(v5);
                    vertices.push_back(v6);
                    vertices.push_back(v7);

                    vertices.push_back(v8);
                    vertices.push_back(v9);
                    vertices.push_back(v10);
                    vertices.push_back(v11);

                    triangles.push_back(tr0);
                    triangles.push_back(tr1);
                    triangles.push_back(tr2);
                    triangles.push_back(tr3);

                    triangles.push_back(tr4);
                    triangles.push_back(tr5);
                    triangles.push_back(tr6);
                    triangles.push_back(tr7);

                    triangles.push_back(tr8);
                    triangles.push_back(tr9);
                    triangles.push_back(tr10);
                    triangles.push_back(tr11);

                    triangles.push_back(tr12);
                    triangles.push_back(tr13);

                    m_nbr_triangle += (12 + 2);


                    index += (8 + 4);
                }else{
                    std::cout << "rentre pas\n";
                }

            }
        }
    }
   /* //coordonnees geometriques des sommets
    vec3 p0=vec3(-125.0f,-0.9f,-125.0f);
    vec3 p1=vec3( 125.0f,-0.9f,-125.0f);
    vec3 p2=vec3( 125.0f,-0.9f, 125.0f);
    vec3 p3=vec3(-125.0f,-0.9f, 125.0f);

    //normales pour chaque sommet
    vec3 n0=vec3(0.0f,1.0f,0.0f);
    vec3 n1=n0;
    vec3 n2=n0;
    vec3 n3=n0;

    //couleur pour chaque sommet
    vec3 c0=vec3(1.0f,1.0f,1.0f);
    vec3 c1=c0;
    vec3 c2=c0;
    vec3 c3=c0;

    //texture du sommet
    vec2 t0=vec2(0.0f,0.0f);
    vec2 t1=vec2(1.0f,0.0f);
    vec2 t2=vec2(1.0f,1.0f);
    vec2 t3=vec2(0.0f,1.0f);

    vertex_opengl v0=vertex_opengl(p0,n0,c0,t0);
    vertex_opengl v1=vertex_opengl(p1,n1,c1,t1);
    vertex_opengl v2=vertex_opengl(p2,n2,c2,t2);
    vertex_opengl v3=vertex_opengl(p3,n3,c3,t3);


    //tableau entrelacant coordonnees-normales
    vertex_opengl geometrie[]={v0,v1,v2,v3};


    //indice des triangles
    triangle_index tri0=triangle_index(0,1,2);
    triangle_index tri1=triangle_index(0,2,3);
    triangle_index index[]={tri0,tri1};
    m_nbr_triangle = 2;*/

    //attribution d'un buffer de donnees (1 indique la création d'un buffer)
    glGenBuffers(1,&m_vbo);                                             PRINT_OPENGL_ERROR();
    //affectation du buffer courant
    glBindBuffer(GL_ARRAY_BUFFER,m_vbo);                                PRINT_OPENGL_ERROR();
    //copie des donnees des sommets sur la carte graphique
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_opengl),&vertices[0],GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();


    //attribution d'un autre buffer de donnees
    glGenBuffers(1,&m_vboi);                                            PRINT_OPENGL_ERROR();
    //affectation du buffer courant (buffer d'indice)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_vboi);                       PRINT_OPENGL_ERROR();
    //copie des indices sur la carte graphique
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,triangles.size() * sizeof(triangle_index),&triangles[0],GL_STATIC_DRAW);  PRINT_OPENGL_ERROR();

    // Chargement de la texture
    load_texture("../data/box.tga",&m_texture_id);
}

float densityFunction(float x, float y, float z)
{


    return 0.0f;
}
void loadPolygons()
{
    /*int dens
    rand*/
}