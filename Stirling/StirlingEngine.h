/*! \file StirlingEngine.h
    \brief Main State header file
    Includes and definitions to enable a main loop within the engine
*/

#ifndef STIRLINGENGINE_H
#define STIRLINGENGINE_H

#include "global_includes.h"
#include "Window.h"
#include "Camera.h"
//#include "Program.h"
#include "Drawable.h"

#define DEFAULT_FOV 45.0f
#define DEFAULT_NEAR_PLANE 0.1f
#define DEFAULT_FAR_PLANE 100.0f

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
	inline void setGameLoop(void(*_gameLoop)()) { gameLoop = _gameLoop; }

    // getters
    inline Window* getWindow() { return &win; }
	inline Camera* getCamera() { return &cam; }

    // adders
    inline void addAsset(Drawable* asset) { assets.push_back(asset); }

    // checkers

private:
    Window win;
	Camera cam;
    
    vector<Program*> shaderPrograms;

    vector<Drawable*> assets;

    int mainLoop();

    glm::vec4 backColor;

	// Projection Matrix
	glm::mat4 projection;

	void (*gameLoop)();
};

#endif