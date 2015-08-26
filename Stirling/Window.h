/*! \file Window.h
    \brief Wrapper for GLFWwindow

    This class is used to customize and initialize GLFWwindow, and access related parameters, such as time
    TODO create key callback stuff
*/

#include "global_includes.h"

#define DEFAULT_WIDTH 800;
#define DEFAULT_HEIGHT 600;
#define DEFAULT_TITLE "Stirling Application"

class Window
{
public:
    Window();
    Window(const char* _title);
    Window(int _width, int _height, const char* _title);

    ~Window();

    // init
    void init();

    /*! \fn step
        \brief window step routine
        Step function that should be called in the main step loop
    */
    void step();

    // getters
    inline int getWidth() { return width; }
    inline int getHeight() { return height; }
    inline const char* getTitle() { return title; }
    GLdouble getTime();
    GLdouble getDT();
    inline GLFWwindow* getWindow() { return window; }

    // checkers
    inline int shouldClose() { return glfwWindowShouldClose(window); }
    bool exists();

private:
    GLFWwindow* window;

    int width, height;
    const char* title;

    GLdouble time; //!< total elapsed time
    GLdouble dtime; //!< time derivative - time since the last getDT() call. Initialized to -1.0 to indicate not yet set
};