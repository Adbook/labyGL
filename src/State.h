//
// Created by adrien on 1/13/17.
//

#ifndef EXECUTABLE_STATE_H
#define EXECUTABLE_STATE_H


class State {
public:
    virtual void update();
    virtual void draw();
    virtual void onLeave();
    virtual void onEnter();
private:
};


#endif //EXECUTABLE_STATE_H
