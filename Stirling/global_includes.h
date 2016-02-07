/*! \file global_includes.h
    \brief Base-line header file containing global definitions, includes, and variables
    
    This file is kept as small as possible, but should contain basic openGL and related library includes
*/

#ifndef GLOBALINCLUDES_H
#define GLOBALINCLUDES_H

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <vector>
#include <fstream>

// TODO make cross platform
//#include <Windows.h>

// SOIL
#include <SOIL.h>

// GLEW
//#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Pempek Assertion library
#define PEMPEK_ASSERT_ENABLED 1
#include "pempek_assert.h"

using namespace std;

#endif