/*! \file StirlineEngine.cpp
    \brief source file for the main state of Stirling Engine
*/

#include "StirlingEngine.h"
// TODO make cross platform
#include <Windows.h>

KeyHandler keyHandler;

StirlingEngine::StirlingEngine() {
    backColor = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
	gameLoop = nullptr;
   keyHandler = KeyHandler();

    shaderPrograms.clear();
    assets.clear();
}

StirlingEngine::~StirlingEngine() {}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   keyHandler.key_callback(window, key, scancode, action, mode);
}

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

    glfwSetKeyCallback(win.getWindow(), key_callback);
    //glfwSetInputMode(win.getWindow(), GLFW_STICKY_KEYS, 1);

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

    PPK_ASSERT_DEBUG(glGetError() == GL_NO_ERROR, "viewport failed to initialize correctly\n");

	cam = Camera(DEFAULT_FOV, win.getWidth() / win.getHeight(), DEFAULT_NEAR_PLANE, DEFAULT_FAR_PLANE);

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

	BOOL bRet;
	MSG msg;
	HWND hWnd = NULL;
	while (!win.shouldClose()) {
		bRet = PeekMessage(&msg, hWnd, 0, 0, 1);
		if (bRet == -1) {
			// handle the error and possibly exit
		}
		else {
			glClearColor(backColor.x, backColor.y, backColor.z, backColor.w);
			glClear(GL_COLOR_BUFFER_BIT);

			// send the game loop to the host main if it exists
			if (gameLoop != nullptr) {
				gameLoop();
			}

			bool edit = false;
			if (cam.edited()) {
				edit = true;
				cam.upToDate();
			}

			for (int i = 0; i < (int)assets.size(); ++i) {
				if (edit) {
					assets[i]->setProjection(cam.getProjectionMatrix());
					assets[i]->setView(cam.getViewMatrix());
				}

				assets[i]->draw();
			}

			glfwSwapBuffers(win.getWindow());
         //glfwPollEvents();

			PPK_ASSERT_WARNING((err = win.exists()), "Stirling is in main loop and window is null - something went very wrong\n");
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
    return err;
}

void StirlingEngine::addKeyHandler(char key, callback keyHandle) {
   keyHandler.add_callback(key, keyHandle);
}