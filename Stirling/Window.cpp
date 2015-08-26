/*! \file Window.cpp
    \brief Window wrapper class
*/

#include "Window.h"

Window::Window() {
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;

    title = DEFAULT_TITLE;

    time = 0.0;
    dtime = -1.0;

    window = glfwCreateWindow(width, height, title, nullptr, nullptr); //TODO enable monitor customization
}

Window::Window(const char* _title) {
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;

    PPK_ASSERT_WARNING(title != nullptr, "Assertion failed - Window title is null - setting to default\n");
    if (title == nullptr) {
        title = DEFAULT_TITLE;
    }
    else {
        title = title;
    }

    time = 0.0;
    dtime = -1.0;

    window = glfwCreateWindow(width, height, title, nullptr, nullptr); //TODO enable monitor customization
}

Window::Window(int _width, int _height, const char* _title) {
    PPK_ASSERT_WARNING(width > 0 && height > 0, "Assertion failed - Window dimensions must be positive integers - setting to default (800,600)\n");
    if (!(_width > 0 && height > 0)) {
        width = DEFAULT_WIDTH;
        height = DEFAULT_HEIGHT;
    }
    else {
        width = _width;
        height = _height;
    }

    PPK_ASSERT_WARNING(title != nullptr, "Assertion failed - Window title is null - setting to default\n");
    if (title == nullptr) {
        title = DEFAULT_TITLE;
    }
    else {
        title = title;
    }

    time = 0.0;
    dtime = -1.0;

    window = glfwCreateWindow(width, height, title, nullptr, nullptr); //TODO enable monitor customization
}

Window::~Window() {
    //if (title != nullptr)
      //  delete title;
    //if (window != nullptr)
      //  window->
}

bool Window::exists() {
    if (window == nullptr) {
        return false;
    }
    return true;
}

void Window::init() {
   // PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "OpenGL issue\n");
    glfwMakeContextCurrent(window);
   // PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "OpenGL issue\n");
    GLenum en = glGetError();// = ;
    while (en  != GL_NO_ERROR) {
        en = glGetError();
        printf("purging gl error queue\n");
        
    }

    PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "OpenGL issue\n");
}

void Window::step() {
    glfwPollEvents();
    time = glfwGetTime();
    PPK_ASSERT_FATAL( time > 0.0, "Assertion failed - glfwGetTime() returned < 0... GLFW error\n");
}

GLdouble Window::getTime() {
    return time;
}

GLdouble Window::getDT() {
    if (dtime < 0) {
        dtime = time;
    }

    GLdouble dt = time - dtime;

    dtime = time;

    return dt;
}