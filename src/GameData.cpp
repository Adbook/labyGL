//
// Created by adrien on 1/13/17.
//

#include "GameData.h"

void GameData::addGameObject(GameObject *obj) {
    gameObjects[nbGameObjects] = obj;
    nbGameObjects ++;
}

GameObject *GameData::getGameObjectById(int i) {
    return getGameObjectByIndex(i);
}

GameObject *GameData::getGameObjectByIndex(int index) {
    if(index >= nbGameObjects){
        std::cout << "GameData.cpp - ERREUR: cet objet n'existe pas" << std::endl;
        return NULL;
    }
    return gameObjects[index];
}

GameData::GameData() {
    nbGameObjects = 0;
}
