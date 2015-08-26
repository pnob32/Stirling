/*! \file StirlineEngine.cpp
    \brief source file for the main state of Stirling Engine
*/

#include "StirlingEngine.h"

StirlingEngine::StirlingEngine() {
    shaderPrograms.clear();
    assets.clear();
}

StirlingEngine::~StirlingEngine() {}

int StirlingEngine::initGL() {

    // GLFW initialization
    GLboolean glfwErr = glfwInit();
    PPK_ASSERT_WARNING(glfwErr == GL_TRUE, "glfwInit() failed - something is rotten here....\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    win = Window();
    win.init();

    if (glfwErr != GL_TRUE) {
        return -1;
    }

    return 1;
}

/*int StirlingEngine::setWindow(Window* window) {//, void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)) {
    win = window;

    // initialized gl context
    if (win == nullptr) {
        return -1;
    }
    win->init();
    glfwSetKeyCallback(win->getWindow(), key_callback);

    return 1;
}*/

int StirlingEngine::initEngine() {
    // GLEW initialization
    glewExperimental = GL_TRUE; //! Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    GLenum glewErr = glewInit();

    GLenum en = glGetError();// = ;
    while (en != GL_NO_ERROR) {
        en = glGetError();
        printf("purging gl error queue\n");

    }
    PPK_ASSERT_WARNING(GLEW_OK == glewErr, "glewInit() failed - something is rotten here.... %s\n", glewGetErrorString(glewErr));
    
    glViewport(0, 0, win.getWidth(), win.getHeight());

    PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "Shader(s) failed to compile correctly\n");

    // return -1 if errors occurred...
    if (glewErr != glewErr) {
        return -1;
    }
    return 1;
}

int StirlingEngine::start() {

    return mainLoop();

    return 1;
}

int StirlingEngine::mainLoop() {
    int err;
    PPK_ASSERT_WARNING((err = win.exists()), "Stirling is about to start the main loop and window is null - something went very wrong\n");
    while (!win.shouldClose()) {
       // cout << "stepping through program loop ";

       // win.step();

        //printf("total time: %f, dt: %f\n", win->getTime(), win->getDT());

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < (int)assets.size(); ++i) {
            assets[i]->draw();
        }
        
        glfwSwapBuffers(win.getWindow());

        PPK_ASSERT_WARNING((err = win.exists()), "Stirling is in main loop and window is null - something went very wrong\n");
    }
    return err;
}