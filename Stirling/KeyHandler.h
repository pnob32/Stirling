/*! \file KeyHandler.h
\brief Header containing glfw key_callback and forwards keystroke handles when needed

*/

#ifndef KEYHANDLER_H
#define KEYHANDLER_H

#include "global_includes.h"
#include <unordered_map>

class KeyHandler
{
public:

   KeyHandler();
   ~KeyHandler();

   void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

   void add_callback(char key, callback keyhandle);

private:
   vector<char> handles;
   unordered_map<char, callback> callback_map;

   bool handlesContain(char key);

};

#endif