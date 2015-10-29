/*! \file Main.cpp
\brief Main program

Main should only contain engine initializations and then branch into step-based time loop
*/

#include "../Stirling/StirlingEngine.h"
#include "../Stirling/TexObject.h"

#define SIMPLE_VERT "shaders/simpletexshader.vert"
#define SIMPLE_FRAG "shaders/simpletexshader.frag"

#define TEX_FILE "../../Assets/Textures/container.jpg"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {

    StirlingEngine engine = StirlingEngine();
    engine.initGL();

    cout << "init'ing engine" << endl;
    engine.initEngine();

    // initiate and compile shader
    Program* shaderProg = new Program();
    shaderProg->setShaderNames(SIMPLE_VERT, SIMPLE_FRAG);
    shaderProg->init();

    shaderProg->bind();
    //shaderProg->addUniform("ourColor");

    TexObject* box = new TexObject(GL_TRIANGLES);

    GLfloat vertices[] = {
        // Positions        // Colors         // Texture Coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left 
    };
    vector<GLfloat> verts;
    verts.clear();
    for (int i = 0; i < 18; ++i) {
        verts.push_back(vertices[i]);
    }

    box->loadLayoutBuffer(verts, 3);
    box->initLayout(2, 8);


    engine.addAsset((Drawable*)box);

    cout << "starting engine" << endl;
    engine.start();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // Is called whenever a key is pressed/released via GLFW
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}