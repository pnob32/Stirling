/*! \file StirlingEngine.h
    \brief Main State header file
    Includes and definitions to enable a main loop within the engine
*/

#include "global_includes.h"
#include "Window.h"
//#include "Program.h"
#include "Drawable.h"

class StirlingEngine {
public:
    StirlingEngine();
    
    ~StirlingEngine();

    // Initializations
    int initGL();
    int initEngine();

    // Starts the main stepper loop
    int start();

    // setters
    //int setWindow(Window* window, void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode));

    // getters
    inline Window* getWindow() { return &win; }

    // adders
    inline void addAsset(Drawable* asset) { assets.push_back(asset); }

    // checkers

private:
    Window win;
    
    vector<Program*> shaderPrograms;

    vector<Drawable*> assets;

    int mainLoop();

   
};