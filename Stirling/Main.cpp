/*! \file Main.cpp
\brief Main program

Main should only contain engine initializations and then branch into step-based time loop

*** Right now, this is mostly test code!! ***
*/

#include "../Stirling/StirlingEngine.h"
#include "../Stirling/TexObject.h"

#define SIMPLE_VERT "shaders/simpletexshader.vert"
#define SIMPLE_FRAG "shaders/simpletexshader.frag"

#define TEX_3D_VERT "shaders/simple3dtexshader.vert"
//#define 3D_TEX_FRAG "shaders/simple"

#define TEX_FILE1 "ExampleAssets/Textures/container.jpg"
#define TEX_FILE2 "ExampleAssets/Textures/awesomeface.png"

// declare engine globally

// declare key callbacks
void keyHandling(); // to handle asynchronous keystrokes (holding keys down without delay)
void ESC_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void w_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void a_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void s_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void d_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

bool w_pressed = false;
bool a_pressed = false;
bool s_pressed = false;
bool d_pressed = false;

vector<TexObject*> objects;
//glm::mat4 boxModel;
TexObject* box;

StirlingEngine* engine;

// test game loop
void gameLoop() {
   keyHandling();
	glm::mat4* boxMod = box->getModel();

	*boxMod = glm::rotate(*boxMod, 0.05f, glm::vec3(0.0f, 0.0f, 1.0f));
	//box->setModel(boxModel);
}

// test key handling
void keyHandling() {
   if (w_pressed) {
      cout << "w is active" << endl;
      engine->getCamera()->translateCamera(glm::vec3(0.0f, 0.0f, 0.1f));
   }
   if (a_pressed) {
      cout << "a is active" << endl;
      engine->getCamera()->translateCamera(glm::vec3(0.1f, 0.0f, 0.0f));
   }
   if (s_pressed) {
      cout << "s is active" << endl;
      engine->getCamera()->translateCamera(glm::vec3(0.0f, 0.0f, -0.1f));
   }
   if (d_pressed) {
      cout << "d is active" << endl;
      engine->getCamera()->translateCamera(glm::vec3(-0.1f, 0.0f, 0.0f));
   }
}

int main() {

   // initialize engine, initialize openGL
   engine = new StirlingEngine();
   engine->initGL();

   // initialize and setup engine
   engine->initEngine();

   // initiate and compile shader
   Program* shaderProg = new Program();
   shaderProg->setShaderNames(TEX_3D_VERT, SIMPLE_FRAG);
   shaderProg->init();

   // bind shader to GPU
   shaderProg->bind();

   // setup custom shader variables
   shaderProg->addUniform("model");
   shaderProg->addUniform("projection");
   shaderProg->addUniform("view");
   shaderProg->addUniform("texture0");
   shaderProg->addUniform("texture1");

   // instantiate and initialize objects
   objects.clear();


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

   // test vertice loading (should be imported by a .obj file loader)
   // TODO: vert file loading
   for (int i = 0; i < 5; ++i) {

      // create new 3D object
      box = new TexObject(GL_TRIANGLES);
      box->embedColor();

      GLuint indices[] = {  // Note that we start from 0!
         0, 1, 3, // First Triangle
         1, 2, 3  // Second Triangle
      };

      // push indices onto index buffer
      vector<GLuint> indexBuf;
      indexBuf.clear();
      for (int i = 0; i < 6; ++i) {
         indexBuf.push_back(indices[i]);
      }

      // push vertices onto vertex buffer
      vector<GLfloat> verts;
      verts.clear();
      //for (int i = 0; i < 32; ++i) {
      for (float vertVal : vertices) {
         verts.push_back(vertVal);// vertices[i]);
      }

      box->loadLayoutBuffer(verts, 36);
      box->initLayout(1, 5);
      box->initTexture(2, 2, 5);

      box->load2DTexture(TEX_FILE1);
      box->load2DTexture(TEX_FILE2);

      box->setShader(shaderProg);

      engine->addAsset((Drawable*)box);

      glm::mat4 boxModel = glm::mat4(1.0f);
      //boxModel = glm::translate(boxModel, glm::vec3(0.0f, 0.0f, -5.0f));
      //boxModel = glm::rotate(boxModel, -55.0f, glm::vec3(1.0f, 0.0f, 0.0f));
      boxModel = glm::translate(boxModel, glm::vec3(0.5f, -0.5f, 0.0f));
      boxModel = glm::rotate(boxModel, (GLfloat)glfwGetTime()
         *
         50.0f, glm::vec3(0.0f,
         0.0f, 1.0f));

      box->setModel(boxModel);

      objects.push_back(box);
   }

   engine->setGameLoop(gameLoop);

   engine->getCamera()->setCameraPosition(glm::vec3(0.0f, 0.0f, -10.0f));

   // set callbacks
   // TODO: GLFW should not need to be used in main... make wrappers... fine for now
   engine->addKeyHandler(GLFW_KEY_ESCAPE, ESC_callback);
   engine->addKeyHandler(GLFW_KEY_W, w_callback);
   engine->addKeyHandler(GLFW_KEY_A, a_callback);
   engine->addKeyHandler(GLFW_KEY_S, s_callback);
   engine->addKeyHandler(GLFW_KEY_D, d_callback);

   cout << "starting engine" << endl;
   engine->start();
}

void ESC_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   glfwSetWindowShouldClose(window, GL_TRUE);
}

void w_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   if (action == GLFW_PRESS)
      w_pressed = true;
   if (action == GLFW_RELEASE)
      w_pressed = false;
}

void a_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   if (action == GLFW_PRESS) {
      a_pressed = true;
   }
   if (action == GLFW_RELEASE) {
      a_pressed = false;
   }
}

void s_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   if (action == GLFW_PRESS)
      s_pressed = true;
   if (action == GLFW_RELEASE)
      s_pressed = false;
}

void d_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
   if (action == GLFW_PRESS)
      d_pressed = true;
   if (action == GLFW_RELEASE)
      d_pressed = false;
}