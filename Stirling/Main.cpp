/*! \file Main.cpp
\brief Main program

Main should only contain engine initializations and then branch into step-based time loop
*/

#include "../Stirling/StirlingEngine.h"
#include "../Stirling/TexObject.h"

#define SIMPLE_VERT "shaders/simpletexshader.vert"
#define SIMPLE_FRAG "shaders/simpletexshader.frag"

#define TEX_3D_VERT "shaders/simple3dtexshader.vert"
//#define 3D_TEX_FRAG "shaders/simple"

#define TEX_FILE1 "../../Assets/Textures/container.jpg"
#define TEX_FILE2 "../../Assets/Textures/awesomeface.png"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

//glm::mat4 boxModel;
TexObject* box;

void gameLoop() {
	glm::mat4* boxMod = box->getModel();

	*boxMod = glm::rotate(*boxMod, 0.05f, glm::vec3(0.0f, 0.0f, 1.0f));
	//box->setModel(boxModel);
}

int main() {

    StirlingEngine engine = StirlingEngine();
    engine.initGL();

    cout << "init'ing engine" << endl;
    engine.initEngine();

    // initiate and compile shader
    Program* shaderProg = new Program();
	shaderProg->setShaderNames(TEX_3D_VERT, SIMPLE_FRAG);
    shaderProg->init();

    shaderProg->bind();

	shaderProg->addUniform("model");
	shaderProg->addUniform("projection");
	shaderProg->addUniform("view");
    shaderProg->addUniform("texture0");
	shaderProg->addUniform("texture1");
	
	//shaderProg->unbind();

    box = new TexObject(GL_TRIANGLES);
	box->embedColor();

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

    /*GLfloat vertices[] = {
        // Positions        // Colors         // Texture Coords
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // Top Left 
    };*/

    GLuint indices[] = {  // Note that we start from 0!
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };

    vector<GLuint> indexBuf;
    indexBuf.clear();
    for (int i = 0; i < 6; ++i) {
        indexBuf.push_back(indices[i]);
    }

    //box->setIndexBuffer(indexBuf);

    vector<GLfloat> verts;
    verts.clear();
    //for (int i = 0; i < 32; ++i) {
	for (float vertVal : vertices ) {
		verts.push_back(vertVal);// vertices[i]);
    }

    box->loadLayoutBuffer(verts, 36);
    box->initLayout(1, 5);
    box->initTexture(2, 2, 5);

    box->load2DTexture(TEX_FILE1);
	box->load2DTexture(TEX_FILE2);

	box->setShader(shaderProg);

    engine.addAsset((Drawable*)box);

	glm::mat4 boxModel = glm::mat4(1.0f);
	//boxModel = glm::translate(boxModel, glm::vec3(0.0f, 0.0f, -5.0f));
	//boxModel = glm::rotate(boxModel, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	boxModel = glm::translate(boxModel, glm::vec3(0.5f, -0.5f, 0.0f));
	boxModel = glm::rotate(boxModel, (GLfloat)glfwGetTime()
		*
		50.0f, glm::vec3(0.0f,
		0.0f, 1.0f));

	box->setModel(boxModel);

	engine.setGameLoop(gameLoop);

	engine.getCamera()->setCameraPosition(glm::vec3(0.0f, 0.0f, -10.0f));

    cout << "starting engine" << endl;
    engine.start();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // Is called whenever a key is pressed/released via GLFW
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}