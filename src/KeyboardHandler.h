//
// Created by adrien on 12/18/16.
//

#ifndef EXECUTABLE_KEYBOARDHANDLER_H
#define EXECUTABLE_KEYBOARDHANDLER_H

#define MAX_KEY_CODE 255
class KeyboardHandler {
public:
    KeyboardHandler();

    void handle_glut_key_down(unsigned char key, int, int);
    void handle_glut_key_up(unsigned char key, int, int);
    void handle_glut_key(bool state, unsigned char keycode);

    bool is_key_down(int key);
    bool is_key_up(int key);
    bool is_any_key_down();

    bool is_any_key_up();
    bool *get_Keys();

private:
    bool m_keys[MAX_KEY_CODE];
};


#endif //EXECUTABLE_KEYBOARDHANDLER_H
