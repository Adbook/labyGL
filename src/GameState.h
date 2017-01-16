//
// Created by adrien on 1/13/17.
//
#define SCREEN_W 1600
#define SCREEN_H 900
#ifndef EXECUTABLE_GAMESTATE_H
#define EXECUTABLE_GAMESTATE_H
#include "State.h"
#include "GameData.h"

class GameState : public State{
public:

    void generateMaze(int size, int *map);
    void update();
    void draw();
    void onLeave();
    void onEnter();

    GameData gdata; //POUR TESTER, BOUGER EN PRIVATE
private:



};


#endif //EXECUTABLE_GAMESTATE_H
