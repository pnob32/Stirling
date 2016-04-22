#include "KeyHandler.h"

KeyHandler::KeyHandler() {
   callback_map.clear();
   handles.clear();
}

KeyHandler::~KeyHandler() {

}

bool KeyHandler::handlesContain(char key) {
   for (int i = 0; i < (int)handles.size(); ++i) {
      if (handles[i] == key) {
         return true;
      }
   }
   return false;
}

void KeyHandler::add_callback(char key, callback keyHandle) {
   pair<char, callback> funcMapping (key, keyHandle);
   callback_map.insert(funcMapping);
   handles.push_back(key);
}

void KeyHandler::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   char keypress = (char)key;
   //if (action != GLFW_PRESS && action != GLFW_REPEAT) {
   //   return;
   //}
   if (handlesContain(key)) {
      callback_map[keypress](window, key, scancode, action, mode);
   }
}