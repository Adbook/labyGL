//
// Created by adrien on 12/18/16.
//

#include "KeyboardHandler.h"

KeyboardHandler::KeyboardHandler() {
    for(int i = 0; i < MAX_KEY_CODE; i++)
        m_keys[i] = false;
}
void KeyboardHandler::handle_glut_key_down(unsigned char key, int, int)
{
    handle_glut_key(true, key);
}

void KeyboardHandler::handle_glut_key_up(unsigned char key, int, int)
{
    handle_glut_key(false, key);
}

void KeyboardHandler::handle_glut_key(bool state, unsigned char keycode)
{
   m_keys[keycode] = state;
}
bool KeyboardHandler::is_key_down(int key)
{
    return m_keys[key];
}
bool KeyboardHandler::is_key_up(int key)
{
    return !is_key_down(key);
}

bool KeyboardHandler::is_any_key_down()
{
    for(int i = 0; i < MAX_KEY_CODE; i++)
    {
        if(m_keys[i] == true)
            return true;
    }
    return false;
}
bool KeyboardHandler::is_any_key_up()
{
    return !is_any_key_up();
}
bool *KeyboardHandler::get_Keys()
{
    return m_keys;
}